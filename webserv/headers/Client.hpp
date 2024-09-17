#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <poll.h>
//#include <sys/event.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <list>
#include "HttpRequest.class.hpp"
#include "HttpRespond.class.hpp"


class Client{

	public:
	Client();
	~Client();

	void acceptConnection(int listeningsocket, int nbclient, fd_set *readset, std::list<Client> *clientlist, int port);
	void checknewconnection(std::list<Client> * clientlist);


	int _client_socket;
	int _clientnumber;
	int _bytesrcv;
	sockaddr_in _client;
	socklen_t _clientsize;
	char _host[NI_MAXHOST];
	time_t _last_msg;
	std::string _buff;
	int _serversocket;
	int _port;
	HttpRequest _req;
	HttpRespond _resp;
	
	private:



};





#endif
