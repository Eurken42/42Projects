#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include "../headers/Socket.hpp"
#include <map>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include "Route.hpp"
// #include <stdlib.h>
#include <cstdlib>

class Route;

class Socket;

class ServerConfig{
	public:

	static Socket *parsefile(std::string filename);
	static void erasewhitespaceleft(std::string str);
	//void configservers(std::string file);
	static std::vector<std::string> splitserv(std::string content);
	static std::vector<std::map<std::string, std::string> > setupmap(std::vector<std::string> configs);
	static int checkdouble(std::string str, std::string tosearch, std::vector<std::map<std::string, std::string> > configs);
	static std::vector<std::map<std::string, Route> > setuproutes(std::vector<std::string> configs);
	static void configservers(std::vector<std::map<std::string, std::string> > configs, std::vector<std::map<std::string, Route> > routes, Socket *serverarray);
	static std::string removespace(std::string key);
	~ServerConfig();
	ServerConfig();



	private:

	std::map<std::string, std::string> _configmap;
};



#endif
