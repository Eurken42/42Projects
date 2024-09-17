#ifndef CGIEXECUTOR_HPP
#define CGIEXECUTOR_HPP

#include <string>
#include "../headers/Socket.hpp"
#include "../headers/Client.hpp"

class Socket;

class CgiExecutor
{
public:
	static std::string
	execute(Client *client, Socket server, std::string cgi_path);
};

#endif //CGIEXECUTOR_H
