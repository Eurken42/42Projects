#ifndef ROUTE_HPP
#define ROUTE_HPP
#include <list>
#include "ServerConfig.hpp"
#include "HttpRequest.class.hpp"
class Route{
public:
	Route();
	~Route();

	std::string _methods;
	std::string _root;
	bool _listing;
	std::string _index;
	std::string _cgi;
	std::string _path;
	std::list<HttpMethod> _method;

private:

};

#endif
