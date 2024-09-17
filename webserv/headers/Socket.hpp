#ifndef SOCKET_HPP
#define SOCKET_HPP

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
#include <fcntl.h>
#include <sys/select.h>
#include <algorithm>
#include <list>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <cstdio>
#include "Client.hpp"
#include "ServerConfig.hpp"
#include "Route.hpp"
// #include "GetRequestHandler.class.hpp"
// #include "PostRequestHandler.class.hpp"
// #include "DeleteRequestHandler.class.hpp"
#include "CgiExecutor.hpp"

class Route;

class Socket{
	public:
		Socket();
		~Socket();
		static void setup(Socket *servers);
		//void handleConnection(int clientsocket);
		//void prepareConnection(int clientsocket);
		static void handleConnection(std::list<Client> *clientlist, Socket *servers);
		static int initsets(std::list<Client> * clientlist, fd_set *_read, fd_set *_write, Socket *servers);
		static int rmfdfromset(int fd, fd_set *set, int max_sock);
		static int addfdtoset(int fd, fd_set *set, int max_sock);
		static void closeconnection(std::list<Client> *clientlist, int i, fd_set *readset, fd_set *writeset);
		static void checktimeout(std::list<Client> *clientlist, fd_set *readset, fd_set *writeset, Socket *sockets);
		static void readrequest(std::list<Client> *clientlist, int fd, long rcv, fd_set *readset, fd_set *writeset, char *buffer);
		int findclient(std::list<Client> *clientlist, int fd);
		static void setMaxSock(std::list<Client> *clientlist);
		static void sendresponse(std::list<Client> *clientlist, int fd, Socket *servers);
		static Route checkroute(Client *client, Socket *server);
	static void sendImage(Client *it);
	sockaddr_in getSockaddr(void);
	void setSockaddr(sockaddr_in server);
	int getListening(void);
	void setListening(int socket);
	char *getSvc(void);
	std::string getServerName(void);
	void setServerName(std::string name);
	int getMaxBodySize(void);
	void setMaxBodySize(int max);
	int getPort(void);
	void setPort(int port);
	std::string getRoot(void);
	void setRoot(std::string root);
	std::map<std::string, Route> getRouteMap(void);
	void setRouteMap(std::string key, Route value);
	std::map<std::string, std::string> getConfigMap(void);
	void setConfigMap(std::map<std::string, std::string> map);
	int getTotalServ(void);
	void setTotalServ(int total);
	static void fillservInfo(struct addrinfo **serverInfo, std::map<std::string, std::string> config);
	static int bindSocket(struct addrinfo *serverInfo);
	static int getListenSock(std::map<std::string, std::string> config);
	std::string getDownload(void);
	void setDownload(std::string str);

	std::string _error;
	std::map<std::string, std::string> _config;

	private:
		sockaddr_in _server;
		int _listening_socket;
		char _svc[NI_MAXSERV];
		std::string _servername;
		int _maxbodysize;
		int _port;
		std::string _root;
		std::map<std::string, Route> _route;
		int _totalserv;
		std::string _download;


};

std::string trimspace(std::string str);




#endif
