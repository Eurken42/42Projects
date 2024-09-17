#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <sys/wait.h>
#include "../headers/CgiExecutor.hpp"
#include <unistd.h>
#include <ctime>
#include <sstream>
#include "../headers/RequestHandler.class.hpp"


static int fork1()
{
	int pid = fork();
	if (pid == -1)
		throw std::runtime_error("fork failed");
	return pid;
}


static std::map<std::string, std::string> get_env(Client *client, Socket server)
{
	std::map<std::string, std::string> env;
	std::map<std::string, std::string> headers = client->_req.getHeaders();

	env["SERVER_SOFTWARE"] = "webserv/1.0";
	env["SERVER_NAME"] = server.getServerName();
	env["GATEWAY_INTERFACE"] = "CGI/1.1";

	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	std::stringstream ss;
	ss << server.getPort();
	env["SERVER_PORT"] = ss.str();
	if (server.getPort())
	{
		std::stringstream port("");
		port << server.getPort();
		env["SERVER_PORT"] = port.str();
	}
	env["REQUEST_METHOD"] = client->_req.getMethodStr();
	env["FILEPATH_INFO"] = client->_req.getPath();
	env["PATH_INFO"] = client->_req.getPath();
	env["SCRIPT_NAME"] = client->_req.getPath();
	env["REMOTE_HOST"] = headers.count("host") ? headers["host"] : "";
	env["REMOTE_USER"] = headers.count("host") ? headers["host"] : "";
	env["CONTENT_TYPE"] = headers.count("content-length") ? headers["content-type"] : "";
	env["CONTENT_LENGTH"] = headers.count("content-length") ? headers["content-length"] : "";
	env["HTTP_ACCEPT"] = headers.count("Accept") ? headers["Accept"] : "";
	env["HTTP_ACCEPT_LANGUAGE"] = headers.count("Accept-Language") ? headers["Accept-Language"] : "";
	env["HTTP_USER_AGENT"] = headers.count("User-Agent") ? headers["User-Agent"] : "";
	env["HTTP_COOKIE"] = headers.count("Cookie") ? headers["Cookie"] : "";
	env["HTTP_REFERER"] = headers.count("Referer") ? headers["Referer"] : "";
	return env;
}

static char **map_to_env(std::map<std::string, std::string> env)
{
	char **envp = new char *[env.size() + 1];
	int i = 0;
	for (std::map<std::string, std::string>::iterator it = env.begin(); it != env.end(); ++it)
	{
		envp[i] = new char[it->second.size() + it->first.size() + 2];
		envp[i] = strcpy(envp[i], (it->first + "=" + it->second).c_str());
		i++;
	}
	envp[i] = NULL;
	return envp;
}

static void free_env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		delete[] envp[i];
		i++;
	}
	delete[] envp;
}

static std::string readAll(int fd, int *size)
{
    std::string result;
    char buff[2048] = {0};
    while (true)
    {
        std::size_t count = read(fd, buff, 2047);
        if (count == 0)
            break;
        buff[count] = 0;
        result += buff;
    }
    if (size)
        *size = result.size();
    return result;
}

std::string
CgiExecutor::execute(Client *client, Socket server, std::string cgi_path)
{
	/// Make env
	std::map<std::string, std::string> env = get_env(client, server);
	char **envp = map_to_env(env);
	/// Make argv
	std::string request_path = client->_req.getPath();
	char *const argv[] = {
			new char[cgi_path.size() + 1],
			new char[request_path.size() + 1],
			NULL
	};

	strcpy(argv[0], cgi_path.c_str());
	argv[0][cgi_path.size()] = '\0';
	strcpy(argv[1], request_path.c_str());
	argv[1][request_path.size()] = '\0';
	if (access(argv[1], F_OK) == -1)
		throw std::runtime_error("file not found");
	if (access(argv[0], X_OK) == -1)
		throw std::runtime_error("file not executable");
	/// Make pipes
	int fd_std[2];
	if (pipe(fd_std))
		throw std::runtime_error("pipe failed");
	int fd_in[2];
	if (pipe(fd_in))
		throw std::runtime_error("pipe failed");
	/// Execute
	int pid;
	pid = fork1();
	if (pid == 0)
	{
		close(fd_in[STDOUT_FILENO]);
		close(fd_std[STDIN_FILENO]);
		dup2(fd_in[STDIN_FILENO], STDIN_FILENO);
		close(fd_in[STDIN_FILENO]);
		dup2(fd_std[STDOUT_FILENO], STDOUT_FILENO);
		close(fd_std[STDOUT_FILENO]);
		execve(cgi_path.c_str(), argv, envp);
		perror("execve: ");
		free_env(envp);
		exit(1);
	}
    delete [] argv[0];
    delete [] argv[1];

	/// Write to stdin
	if (client->_req.getMethod() == GET)
		write(fd_in[STDOUT_FILENO], client->_req.getQuery().c_str(), client->_req.getQuery().size());
	else if (client->_req.getMethod() == POST)
		write(fd_in[STDOUT_FILENO], client->_req.getBody().c_str(), client->_req.getBody().size());

	/// Close pipes and free memory
	close(fd_in[STDOUT_FILENO]);
	close(fd_in[STDIN_FILENO]);
	close(fd_std[STDOUT_FILENO]);
	free_env(envp);

	/// Wait for child and check for timeout
	const int S_TIMEOUT = 2;
	std::time_t s_start = std::time(NULL);
	bool did_timeout;
	int exit_status = 0;
	while (true)
	{
		std::time_t elapsed = std::time(NULL) - s_start;
		did_timeout = (elapsed >= S_TIMEOUT);
		if (did_timeout)
			break;
		exit_status = -1;
		waitpid(pid, &exit_status, WNOHANG);
		if (exit_status != -1)
		{
			exit_status = WEXITSTATUS(exit_status);
			break;
		}
		usleep(10000);
	}

	/// Read from stdout
    std::string result;
	if (did_timeout)
	{
		std::cerr << "CGI timed out" << std::endl;
		result = "timeout";
	}
	else
		result = readAll(fd_std[STDIN_FILENO], NULL);
	if (exit_status != 0)
		std::cerr << "CGI exited with " << exit_status << std::endl;
	close(fd_std[STDIN_FILENO]);
	return result;
}
