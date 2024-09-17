#include "Socket.hpp"
#include "HttpRequest.class.hpp"
#include "GetRequestHandler.class.hpp"
#include "PostRequestHandler.class.hpp"
#include "DeleteRequestHandler.class.hpp"

int max_sock;

sockaddr_in Socket::getSockaddr(void)
{
	return this->_server;
}

void Socket::setSockaddr(sockaddr_in server)
{
	this->_server = server;
}

int Socket::getListening(void)
{
	return this->_listening_socket;
}

void Socket::setListening(int socket)
{
	this->_listening_socket = socket;
}

char *Socket::getSvc(void)
{
	return this->_svc;
}

std::string Socket::getServerName(void)
{
	return this->_servername;
}

void Socket::setServerName(std::string name)
{
	this->_servername = name;
}

int Socket::getMaxBodySize(void)
{
	return this->_maxbodysize;
}

void Socket::setMaxBodySize(int max)
{
	this->_maxbodysize = max;
}

int Socket::getPort(void)
{
	return this->_port;
}

void Socket::setPort(int port)
{
	this->_port = port;
}

std::string Socket::getRoot(void)
{
	return this->_root;
}

void Socket::setRoot(std::string root)
{
	this->_root = root;
}

std::map<std::string, Route> Socket::getRouteMap(void)
{
	return this->_route;
}

void Socket::setRouteMap(std::string key, Route value)
{
	this->_route[key] = value;
}

std::map<std::string, std::string> Socket::getConfigMap(void)
{
	return this->_config;
}

void Socket::setConfigMap(std::map<std::string, std::string> map)
{
	this->_config = map;
}

int Socket::getTotalServ(void)
{
	return this->_totalserv;
}

void Socket::setTotalServ(int total)
{
	this->_totalserv = total;
}

std::string Socket::getDownload(void)
{
	return this->_download;
}

void Socket::setDownload(std::string str)
{
	this->_download = str;
}

Socket::Socket()
{
	memset(&_svc, 0, sizeof(_svc));
}

Socket::~Socket()
{

}

void Socket::fillservInfo(struct addrinfo **serverInfo, std::map<std::string, std::string> config)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (int retval = getaddrinfo(NULL, config["port"].c_str(), &hints, serverInfo) != 0)
	{
		std::cerr << "GetAddrInfo error: " << gai_strerror(retval) << std::endl;
		exit(123);
	}
	return;
}

int Socket::bindSocket(struct addrinfo *serverInfo)
{
	int listenSockFd;
	int yes = 1;

	struct addrinfo *infoPtr = NULL;
	for (infoPtr = serverInfo; infoPtr != NULL; infoPtr = infoPtr->ai_next)
	{
		listenSockFd = socket(infoPtr->ai_family, infoPtr->ai_socktype, infoPtr->ai_protocol);
		if (listenSockFd == -1)
		{
			perror("socket: ");
			continue;
		}

		if (setsockopt(listenSockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1){
			perror("setsockopt: ");
			close(listenSockFd);
			continue;
		}

		if (bind(listenSockFd, infoPtr->ai_addr, infoPtr->ai_addrlen) == -1)
		{
			perror("bind: ");
			close(listenSockFd);
			continue;
		}
		else
			break;
	}
	if (infoPtr == NULL)
		return -1;
	return (listenSockFd);
}

int Socket::getListenSock(std::map<std::string, std::string> config)
{
	int listenSockFd;
	struct addrinfo* serverInfo;

	fillservInfo(&serverInfo, config);
	listenSockFd = bindSocket(serverInfo);
	freeaddrinfo(serverInfo);

	if (listenSockFd == -1)
	{
		perror("listening socket == -1: ");
		exit(1);
	}
	if (listen(listenSockFd, 128) == -1)
	{
		perror("listen == -1: ");
		exit(1);
	}
	if (fcntl(listenSockFd, F_SETFL, O_NONBLOCK) == -1)
	{
		perror("fcntl == -1: ");
		exit(1);
	}
	return listenSockFd;
}

void Socket::setup(Socket *servers)
{
	for (int i = 0; i < servers[0]._totalserv; i++)
	{
//		servers[i]._listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	
		int yes = 1;

		servers[i]._listening_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		if (servers[i]._listening_socket < 0)
		{
			std::cerr << "Socket creation impossible" << std::endl;
			exit(1);
		}

		servers[i]._server.sin_family = AF_INET;
		servers[i]._server.sin_port = htons(servers[i]._port);
		servers[i]._server.sin_addr.s_addr = INADDR_ANY;

		if (setsockopt(servers[i]._listening_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		{
			std::cerr << "setsockopt error cheh (" << strerror(errno) << ")" << std::endl;
			exit(-9);
		}

		if (bind(servers[i]._listening_socket, (sockaddr *)&servers[i]._server, (socklen_t)sizeof(servers[i]._server)) < 0)
		{
			std::cerr << "Error during socket binding (" << strerror(errno) << ")" << std::endl;
			exit(2);
		}


		if (listen(servers[i]._listening_socket, 128) < 0)
		{
			std::cerr << "Error while listening on socket (" << strerror(errno) << ")" << std::endl;
			exit(3);
		}

		if (fcntl(servers[i]._listening_socket, F_SETFL, O_NONBLOCK) < 0)
		{
			std::cerr << "Error with fcntl (" << strerror(errno) << ")" << std::endl;
			exit(4);
		}
	}
	//freeaddrinfo(servers[0]._info);
}

int	Socket::initsets(std::list<Client> * clientlist, fd_set *_read, fd_set *_write, Socket *servers)
{
	int res = 0;
	FD_ZERO(_read);
	FD_ZERO(_write);

	for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
		if(it->_client_socket > 0)
		{
			FD_SET(it->_client_socket, _read);
			FD_SET(it->_client_socket, _write);
		}
		else
		{
			FD_CLR(it->_client_socket, _read);
			FD_CLR(it->_client_socket, _write);
		}
	}

	for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
			res = std::max(res, it->_client_socket);
	}
	int i = 0;

	while (i < servers[0]._totalserv)
	{
		FD_SET(servers[i]._listening_socket, _read);
		res = std::max(res, servers[i]._listening_socket);
		i++;
	}
	return res;
}

int checkport(int i, Socket *servers)
{
	for (int j = 0; j < servers[0].getTotalServ(); j++)
	{
		if (servers[j].getListening() == i)
			return servers[j].getPort();
	}
	return -1;
}

int checklisteningsock(int i, Socket *servers)
{
	for (int j = 0; j < servers[0].getTotalServ(); j++)
	{
		if (servers[j].getListening() == i)
			return i;
	}
	return -1;
}

bool clienterase(Client client)
{
	if (client._client_socket == -2)
		return true;
	return false;
}

void Socket::handleConnection(std::list<Client> * clientlist, Socket *servers)
{
	long rcv = 0;
	std::string str;
	char buffer[409600];
	fd_set readcpy;
	fd_set writecpy;
	fd_set readset;
	fd_set writeset;
	timeval timeout;
	std::list<Client>::iterator tmp;
	initsets(clientlist, &readset, &writeset, servers);

	FD_ZERO(&readcpy);
	FD_ZERO(&writecpy);
	while(1)
	{
		clientlist->remove_if(clienterase);
		readcpy = readset;
		writecpy = writeset;
		memset(buffer, 0, sizeof(buffer));
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		for (int i = 0; i < servers[0]._totalserv; i++)
		{
			if (max_sock < servers[i]._listening_socket)
				max_sock = servers[i]._listening_socket;
		}
		for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
		{
			max_sock = std::max(max_sock, it->_client_socket);
		}
		rcv = select(max_sock + 1, &readcpy, &writecpy, NULL, &timeout);

		if (rcv < 0)
		{
			perror("select");
			std::cerr << max_sock << " | " << clientlist->size() << std::endl;
			exit(1);
		}
		else if (rcv == 0)
		{
			//std::cout << "max_sock = " << max_sock << std::endl;
		}
		else
		{
			memset(buffer, 0, sizeof(buffer));
			for (int i = 0; i <= max_sock; i++)
			{
							
				if(FD_ISSET(i, &readcpy) && checklisteningsock(i, servers) == i)
				{

					clientlist->back().acceptConnection(checklisteningsock(i, servers), clientlist->size() - 1, &readset, clientlist, checkport(i, servers));
					if (clientlist->back()._client_socket != -1)
						max_sock = addfdtoset(clientlist->back()._client_socket, &readset, max_sock);
					clientlist->back().checknewconnection(clientlist);
				}
				else if (FD_ISSET(i, &readcpy) && i != checklisteningsock(i, servers))
				{
					memset(buffer, 0, sizeof(buffer));
					rcv = recv(i, buffer, 409600, 0);
				//	std::cout << buffer << std::endl;
					readrequest(clientlist, i, rcv, &readset, &writeset, buffer);
				}
				else if (FD_ISSET(i, &writecpy))
				{
					for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
					{
						if (it->_client_socket == i)
						{
							sendresponse(clientlist, i, servers);
							if (it->_req.keepAlive() == false)
							{
								// std::cout << std::endl << "close the connection with the client" << std::endl;
								closeconnection(clientlist, i, &readset, &writeset);
							}
							else
							{
								// std::cout << std::endl << "keep the connection with the client" << std::endl;
								max_sock = rmfdfromset(i, &writeset, max_sock);
								max_sock = addfdtoset(i, &readset, max_sock);
								it->_req.resetRequest();
							}
							break;
						}
					}
				}
				rcv = 0;
			}
		}
		checktimeout(clientlist, &readset, &writeset, servers);
	}
}


int Socket::rmfdfromset(int fd, fd_set *set, int max_sock)
{
	if (fd == max_sock)
		max_sock--;
	FD_CLR(fd, set);
	return max_sock;
}

int Socket::addfdtoset(int fd, fd_set *set, int max_sock)
{
	FD_SET(fd, set);
	if (max_sock < fd)
		max_sock = fd;
	return max_sock;
}

void Socket::closeconnection(std::list<Client> *clientlist, int i, fd_set *readset, fd_set *writeset)
{
	for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
		if (it->_client_socket == i)
		{
			std::cout << "Client [" << it->_clientnumber << "] disconnected" << std::endl;
			//if (FD_ISSET(i, &readset))
			max_sock = rmfdfromset(i, readset, max_sock);
			//if (FD_ISSET(i, &writeset))
			max_sock = rmfdfromset(i, writeset, max_sock);
			//close(it->_client_socket);
			if(close(i) != 0)
			{
				perror("close");
				exit(3);
			}
			close(it->_client_socket);
			it->_client_socket = -2;
			//setMaxSock(clientlist);
			//clientlist->erase(it);
			break;
		}
	}
}

void Socket::checktimeout(std::list<Client> *clientlist, fd_set *readset, fd_set *writeset, Socket *sockets)
{
	(void)sockets;
	for ( std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
			if (time(NULL) - it->_last_msg > 5 && it->_client_socket != -1)
			{
				std::cerr << "Client number {" << it->_clientnumber << "} has timed out" << std::endl;
				// sendresponse(clientlist, it->_client_socket, sockets);


				//	PERMET DE NOTIFIER LE CLIENT D'UN TIMEOUT
				//	MAIS SI LE CLIENT NE FAIS PAS DE REQUETE PENDANT 5s
				//	LE TIMEOUT SERA ENVOYER A LA PROCHAINE CONNEXION

				// int	i = 0;
				// while (sockets[i]._listening_socket != it->_serversocket)
				// 	i++;
				// GetRequestHandler	methodHandler;
				// std::string	tmp = ".";
				// it->_req.setParsing(PARSING_DONE);
				// it->_req.setErrorCode(408);
				// it->_req.setPathRelative(tmp);
				// it->_resp = methodHandler.handleRequest(&(it->_req), &*it, sockets[i]);

				// write(it->_client_socket, it->_resp.getResp().c_str(), strlen(it->_resp.getResp().c_str()));

				closeconnection(clientlist, it->_client_socket, readset, writeset);
				//setMaxSock(clientlist);
			}
	}
}

void Socket::readrequest(std::list<Client> *clientlist, int fd, long rcv, fd_set *readset, fd_set *writeset, char *buffer)
{
	std::string str;


	if (rcv < 0)
	{
		closeconnection(clientlist, fd, readset, writeset);
		//setMaxSock(clientlist);
		std::cerr << "error: recv" << std::endl;
		exit(1);
	}
	else if (rcv == 0)
	{
		closeconnection(clientlist, fd, readset, writeset);
		//setMaxSock(clientlist);
	}
	else
	{
		for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
		{
			if (fd == it->_client_socket)
			{
				it->_buff = std::string(buffer, rcv);
				it->_last_msg = time(NULL);
				it->_bytesrcv = rcv;
				max_sock = addfdtoset(fd, writeset, max_sock);
				max_sock = rmfdfromset(fd, readset, max_sock);

				std::cout << "Respond received to Client " << it->_clientnumber << " on socket : " << it->_client_socket << " on port: "<< it->_port << std::endl;
				//str = buffer;
				break;
			}
		}
	}
}

int Socket::findclient(std::list<Client> *clientlist, int fd)
{
	int i = 1;
	for(std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
		if (it->_client_socket == fd)
			return i;
		i++;
	}
	return 0;
}

void Socket::setMaxSock(std::list<Client> *clientlist)
{
	for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
		if (it->_client_socket > max_sock)
			max_sock = it->_client_socket;
	}
}

void Socket::sendresponse(std::list<Client> *clientlist, int fd, Socket *servers)
{
	std::string response;
	std::ifstream file;
	std::string filename = "";
	std::string line;
	std::string cgiresp = "";
	std::string hostname  = "";
	std::string server_hostname  = "";

	for (std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	{
		if (it->_client_socket == fd && it->_bytesrcv > 0)
		{
			int	i = 0;
			while (servers[i]._listening_socket != it->_serversocket)
				i++;
			it->_req.parse(it->_buff.c_str(), it->_bytesrcv, servers[i].getMaxBodySize() - 1);
			hostname = it->_buff.substr(it->_buff.find("Host:") + 6, it->_buff.find_first_of("\n", it->_buff.find("Host:")) - it->_buff.find("Host:") - 6);
			server_hostname = servers[i].getServerName();
			if (hostname.substr(0, hostname.find(":")) != server_hostname && hostname.find("localhost") == std::string::npos)
			{
				it->_req.setErrorCode(400);
			}
			if (std::atoi(hostname.substr(hostname.find(":") + 1, hostname.length() - hostname.find(":")).c_str()) != servers[i].getPort() && servers[i].getPort() != 80)
			{
				// std::cout << atoi(hostname.substr(hostname.find(":") + 1, hostname.length() - hostname.find(":")).c_str() + 1)<< std::endl;
				// std::cout << servers[i].getPort() << std::endl;
				it->_req.setErrorCode(400);
			}
			//std::cout << it->_req.getBody().find("Host:") << std::endl;
			Route	rt;
			rt = checkroute(&*it, servers);
			//std::cout << it->_req.getMethodStr() << std::endl;
			//std::cout << rt._methods << std::endl;
			if (!it->_req.isParsingDone())
				std::cerr << "Bad request in sendreponse" << std::endl;
			else if (it->_req.getPath().empty())
				it->_req.setErrorCode(400);
			else if ((it->_req.getPathRelative()).empty())
			{
				it->_req.setErrorCode(404);
				std::cerr << "Relative path not found" << std::endl;
			}
			switch(it->_req.getMethod())
			{
				//	METTRE LES CONFIG DANS LES CREATIONS DES methodHandler
				case GET:
				{
					GetRequestHandler	methodHandler;
					if (it->_req.getErrorCode() == 0 && rt._methods.find("GET") == std::string::npos)
						it->_req.setErrorCode(405);
					it->_resp = methodHandler.handleRequest(&(it->_req), &*it, servers[i]);
					break;
				}
				case POST:
				{
					PostRequestHandler	methodHandler;
					if (it->_req.getErrorCode() == 0 && rt._methods.find("POST") == std::string::npos)
						it->_req.setErrorCode(405);
					it->_resp = methodHandler.handleRequest(&(it->_req), &*it, servers[i]);
					break;
				}
				case DELETE:
				{
					DeleteRequestHandler	methodHandler;
					if (it->_req.getErrorCode() == 0 && rt._methods.find("DELETE") == std::string::npos)
						it->_req.setErrorCode(405);
					it->_resp = methodHandler.handleRequest(&(it->_req), &*it, servers[i]);
					break;
				}
				case NONE:
				{
					GetRequestHandler	methodHandler;
					it->_resp = methodHandler.handleRequest(&(it->_req), &*it, servers[i]);
					break;
				}
			}
			if (it->_req.getPath() == "./www/index2.html")
			{
				it->_req.setErrorCode(301);
				it->_resp.setBody(openReadFile("./www/redir.html"));
				it->_resp.build(it->_req);
			}
			else if (it->_req.getPath().find("upload") != std::string::npos)
			{
				it->_req.setErrorCode(200);
				it->_resp.setBody(openReadCloseDir("./" + servers[i].getDownload(), "./" + servers[i].getDownload()));
				it->_resp.build(it->_req);
			}
			if (it->_req.getPath().find("png") != std::string::npos || it->_req.getPath().find("jpg") != std::string::npos || it->_req.getPath().find("jpeg") != std::string::npos || it->_req.getPath().find("ico") != std::string::npos)
				sendImage(&*it);
			else
				send(it->_client_socket, it->_resp.getResp().c_str(), it->_resp.getResp().length() , 0);
			std::cout << "Respond sended to Client " << it->_clientnumber << " on socket : " << it->_client_socket << " on port: "<< it->_port << std::endl;
			if (it->_req.keepAlive() == true)
			{
				it->_req.resetRequest();
				it->_req.setKeepAlive(true);
			}
			it->_buff.erase();
			it->_bytesrcv = 0;
		}
	}
}

void Socket::sendImage(Client *it)
{
	std::ostringstream responseStream;
	std::ifstream imageFile(it->_req.getPath());

	if (!imageFile) {
		responseStream << "HTTP/1.1 404 Not Found\r\n\r\n";
		return;
	}

	// Obtenir la taille du fichier
	imageFile.seekg(0, std::ios::end);
	std::streampos fileSize = imageFile.tellg();
	imageFile.seekg(0, std::ios::beg);

	// Lire le contenu du fichier image
	std::vector<char> buffer(fileSize);
	if (!imageFile.read(buffer.data(), fileSize)) {
		responseStream << "HTTP/1.1 500 Internal Server Error\r\n\r\n";
		return;
	}

	// Envoyer la réponse HTTP avec l'image
	responseStream << "HTTP/1.1 200 OK\r\n";
	responseStream << "Content-Type: ";
	responseStream << it->_resp.getHeader("Content-Type");
	responseStream << "\r\n";
	responseStream << "Content-Length: " << fileSize << "\r\n\r\n";
	responseStream.write(buffer.data(), fileSize);
	send(it->_client_socket, responseStream.str().c_str(), responseStream.str().length(), 0);
}

std::string trimspace(std::string str)
{
	std::string res;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isspace(str[i]) != true)
			res += str[i];
	}
	return res;
}

Route	Socket::checkroute(Client *client, Socket *server)
{
	Route	rt;
	int i = 0;

	while (server[i]._listening_socket != client->_serversocket)
		i++;
	std::string filepath = client->_req.getPath();
	std::string route = filepath.substr(0, filepath.find_last_of("/") + 1);
	route.erase(0, 5);
	std::string	final_route = "";
	for(std::map<std::string, Route>::iterator it = server[i]._route.begin(); it != server[i]._route.end(); it++)
	{
		if (route.find(it->first) == 0)
		{
			if (final_route.size() < it->first.size())	
				final_route = it->first;
		}
	}
	if (server[i]._route.count(final_route) == 0)
	{
		std::cerr << "Route pas accessible avec le port du client : "  << filepath << std::endl;
		filepath.clear();
		return rt;
	}
	rt = server[i]._route[final_route];

	DIR*	dir;
	if (client->_req.getPath().empty())
	{
		std::cerr << "Path from request empty" <<std::endl;
		return rt;
	}
	while(filepath.find_first_of(" ") != std::string::npos)
		filepath.erase(filepath.find_first_of(" "), 1);
	if (filepath.find(final_route) != std::string::npos)
		filepath.replace(filepath.find(final_route), final_route.length(), rt._root);
	if ((dir = opendir(filepath.c_str())) != NULL)
	{
		if (rt._listing)
		{
			closedir(dir);
			client->_req.setDirectory(true);
			client->_req.setPathRelative(filepath);
		}
		else
		{
			filepath += rt._index;
			if (access(filepath.c_str(), F_OK | R_OK) == 0)
			{
				client->_req.setDirectory(false);
				client->_req.setPathRelative(filepath);
			}
		}
	}
	else if (access(filepath.c_str(), F_OK | R_OK) == 0)
	{
		client->_req.setDirectory(false);
		client->_req.setPathRelative(filepath);
	}
	else if (access(filepath.c_str(), F_OK) == 0)
	{
		client->_req.setPathRelative(filepath);
		client->_req.setDirectory(false);
		client->_req.setErrorCode(403);
	}
	else
	{
		filepath.clear();
		std::cerr << "Dir and File not accessible" << std::endl;
	}
	return rt;
}
