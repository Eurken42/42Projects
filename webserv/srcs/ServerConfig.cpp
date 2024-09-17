#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
{
	_configmap["port"] = "default";
	_configmap["servername"] = "default";
	_configmap["maxbodysize"] = "default";
	_configmap["root"] = "default";
}

ServerConfig::~ServerConfig()
{

}

void ServerConfig::erasewhitespaceleft(std::string str)
{
	while (isspace(str[0]))
		str = str.erase(0);
}

Socket *ServerConfig::parsefile(std::string filename)
{
	std::ifstream file;
	std::string content;
	std::string line;
	std::vector<std::string> configs;
	std::vector<std::map<std::string, std::string> > res;
	std::vector<std::map<std::string, Route> >routes;

	file.open(filename.c_str());

	if (!file.is_open())
	{
		std::cerr << "cannot open file " << filename << std::endl;
		exit(1);
	}
	while (std::getline(file, line))
	{
		size_t comm_pos = line.find("#");
		if (comm_pos != std::string::npos)
		{
			line = line.substr(0, comm_pos);
			erasewhitespaceleft(line);
		}
		if (!line.empty())
			content += line;
		content += '\n';
	}
	file.close();
	
	if (filename.find(".UDC") != filename.size() - 4)
	{
		std::cerr << "Bad file extension" << std::endl;
		exit(1);
	}
	if (content.substr(0, 9) != "servers:\n")
	{
		std::cerr << "invalid config file: 'servers' keyword missing on first line" << std::endl;
		exit(1);
	}

	content = content.erase(0, 9);

	configs = splitserv(content);
	int nbserv = configs.size();
	routes = setuproutes(configs);
	//leaks here
	res = setupmap(configs);
	Socket *serverarray = new Socket[nbserv];
	configservers(res, routes, serverarray);
	serverarray[0].setTotalServ(nbserv);
	return serverarray;
}

std::string ServerConfig::removespace(std::string key)
{
	size_t i = 0;
	std::string res;
	while (i < key.size())
	{
		if (isspace(key[i]) == false)
			res += key[i];
		i++;
	}
	return res;
}

void ServerConfig::configservers(std::vector<std::map<std::string, std::string> > configs, std::vector<std::map<std::string, Route> > routes, Socket *serverarray)
{

	size_t i = 0;
	for (std::vector<std::map<std::string, std::string> >::iterator it = configs.begin(); it != configs.end(); it++)
	{
		std::map<std::string, std::string> maptmp = *it;
		serverarray[i].setPort(atoi(maptmp["port"].c_str()));
		serverarray[i].setMaxBodySize(atoi(maptmp["clientbody"].c_str()));
		serverarray[i].setServerName(removespace(maptmp["server_name"]));
		serverarray[i].setDownload(removespace(maptmp["download"])) ;
		serverarray[i]._error = removespace(maptmp["error"]);
		serverarray[i]._config = maptmp;
		i++;
	}
	i = 0;
	for (std::vector<std::map<std::string, Route> >::iterator it = routes.begin(); it != routes.end() && i < (size_t)serverarray[0].getTotalServ(); it++)
	{
		std::map<std::string, Route> maptmp = *it;
		std::string key;
		for (std::map<std::string, Route>::iterator it2 = maptmp.begin(); it2 != maptmp.end(); it2++)
		{
			if (it2->first == "NEXT" && it2->second._path == "true")
			{
				i++;
				break;
			}
			key = it2->first;
			key = removespace(key);
			serverarray[i].setRouteMap(key, it2->second);
		}
	}
	i = 0;
}


std::vector<std::string> ServerConfig::splitserv(std::string content)
{
	std::string res;
	std::vector<std::string> vector;
	int servstart;
	//int servend;

	while (content.size() > 0)
	{
		if (content.find("@")  == std::string::npos)
		{
			content.clear();
			return vector;
		}
		servstart = content.find("@");
		if (content.substr(servstart, servstart + 7) != "@server[\n")
		{
			// std::cout << content.substr(servstart, servstart + 7) << std::endl;
			std::cerr << "Bad syntax, example: @server[...]" << std::endl;
			exit(1);
		}
		content = content.substr(servstart + 9, content.size());
		res = content.substr(0, content.find_first_of(']'));
		content = content.substr(content.find_first_of("]") + 1, content.size());
		vector.push_back(res);
		if (content.find('\n') != 0)
		{
			std::cerr << "Bad syntax, missing newline after server" << std::endl;
			exit(1);
		}
		while(content[0] == '\n')
			content.erase(0, 1);
	}
	return vector;
}

std::vector<std::map<std::string, std::string> > ServerConfig::setupmap(std::vector<std::string> configs)
{
	std::vector<std::map<std::string, std::string> > res;
	std::map<std::string, std::string> maptmp;
	std::string tmp;
	size_t pos;
	std::string i = "1";
	
	for (std::vector<std::string>::iterator it = configs.begin(); it != configs.end(); it++)
	{
		pos = it->find("- server_name =");
		//std::cout << "pos = \"" << pos << "\"" << std::endl;
		//std::cout << "Index ; = \"" << it->find(";", pos) - pos << "\"" << std::endl;
		//std::cout << "it is === \"" << *it << "\"" << std::endl;
		if (pos == std::string::npos)
		{
			std::cerr << "Config file: server name not found, default name given" << std::endl;
			tmp  = "default " + i;
			std::cerr << "default:" << tmp << std::endl;
			maptmp["server_name"] = tmp;
			i[0]++;
		}
		else
		{
			
			//std::cout << "pos = \"" << pos << "\"" << std::endl;
			tmp = it->substr(pos + 16, it->find(";", pos) - pos);
			//std::cout << "Value tmp -> \"" << tmp << "\"" << std::endl;
			if (tmp.find_first_of('\n') != tmp.find_last_of("\n") || tmp.find_first_of(";") != tmp.find_last_of(";"))
			{
				std::cerr << "Config file: server_name: bad syntax" << std::endl;
				exit(1);
			}
			//std::cout << "Value tmp before erase -> \"" << tmp << "\"" << std::endl;
			if (tmp.find("\n") != std::string::npos)
				tmp.erase(tmp.find("\n"));
			if (tmp.find(";") != std::string::npos)
				tmp.erase(tmp.find(";"));
			//std::cout << "Value tmp after erase -> \"" << tmp << "\"" << std::endl;
			if (checkdouble(tmp, "server_name", res) != 0)
			{
				std::cerr << "Config file: two server cannot have the same name" << std::endl;
				exit(1);
			}
			maptmp["server_name"] = tmp;
		}
		pos = it->find("- listen =");
		if (pos == std::string::npos)
		{
			std::cerr << "Config file: listening port not found, syntax is: - listen = [...];" << std::endl;
			exit(1);
		}
		tmp = it->substr(pos + 11, it->find(";"));
		if (tmp.find_first_of('\n') != tmp.find_last_of("\n") || tmp.find_first_of(";") != tmp.find_last_of(";"))
		{
			std::cerr << "Config file: port: bad syntax" << std::endl;
			exit(1);
		}
		tmp.erase(tmp.find("\n"));
		tmp.erase(tmp.find(";"));
		if (checkdouble(tmp, "port", res) || atoi(tmp.c_str()) == 0)
		{
			std::cerr << "Config file: two server cannot listen on the same port" << std::endl;
			exit(1);
		}
		maptmp["port"] = tmp;
		pos = it->find("- clientbody =");
		
		if (pos == std::string::npos)
		{
			std::cerr << "Config file: client max body size not found, syntax is: - clientbody = [...];" << std::endl;
			exit(1);
		}
		tmp = it->substr(pos + 14, it->find(";"));
		tmp.erase(tmp.find("\n"));
		tmp.erase(tmp.find(";"));
		maptmp["clientbody"] = tmp;

		if (it->find("- error =") != std::string::npos)
		{	std::string ntm;
			ntm = it->substr(it->find("- error =") + 10, it->find_first_of(";"));
			ntm.erase(ntm.find(";"), ntm.size());
			
			maptmp["error"] = ntm;
			// maptmp["error"].erase(maptmp["error"].find(";"));
			// maptmp["error"].erase(maptmp["error"].find("\n"));
		}
		else
		{
			maptmp["error"] = "./errfile/";
		}

		if (it->find("- download =") != std::string::npos)
		{	
			pos = it->find("- download =") + 12; 
			std::string dldir = it->substr(pos, it->find(";", pos) - pos);
			DIR *directory = opendir(removespace(dldir).c_str());
			if (directory == NULL)
			{
				std::cerr << "Directory " << dldir << " does not exist, please create it or change the download folder in the config" << std::endl;
				exit(1);
			}
			maptmp["download"] = removespace(dldir);
			closedir(directory);
		}
		else
		{
			maptmp["download"] = "upload";
		}
		// std::cout << "FINAL NAME IS --------- \"" << maptmp["download"] << "\"" << std::endl;
		res.push_back(maptmp);
		maptmp.clear();
	}
	//exit(1);
	return res;
}

std::vector<std::map<std::string, Route> > ServerConfig::setuproutes(std::vector<std::string> configs)
{
	size_t pos = 0;
	std::string tmp;
	std::string tmp2;
	std::string route;
	std::map<std::string, Route> maptmp;
	std::vector<std::map<std::string, Route> > res;
	for (std::vector<std::string>::iterator it = configs.begin(); it != configs.end(); it++)
	{
		pos = it->find("- route{");
		if (pos == std::string::npos)
		{
			std::cerr << "Config file: route not found" << std::endl;
			exit(1);
		}
		tmp = it->substr(pos + 8, it->find_first_of("}"));
		while (tmp.size() != 0)
		{
			if (tmp.find("-") == std::string::npos || tmp.find("(") == std::string::npos)
			{
				std::cerr << "Config file: bad route syntax" << std::endl;
				exit(1);
			}
			tmp2 = tmp.substr(tmp.find("-") + 1, tmp.find("("));
			tmp2 = tmp2.substr(0, tmp2.find("("));
			maptmp[tmp2]._path = tmp2;
			route = tmp.substr(0, tmp.find_first_of(")"));
			if (route.find("methods =") == std::string::npos)
			{
				std::cerr << "Config file: route methods not found" << std::endl;
				exit(1);
			}
			maptmp[tmp2]._methods = route.substr(route.find("methods =") + 9, route.find(";", route.find("methods =")) - route.find("methods ="));
			maptmp[tmp2]._methods.erase(maptmp[tmp2]._methods.find(";"));
			if (route.find("root =") == std::string::npos)
			{
				std::cerr << "Config file: route root not found" << std::endl;
				exit(1);
			}
			maptmp[tmp2]._root = removespace(route.substr(route.find("root =") + 6, route.find(";", route.find("root =")) - route.find("root =")));
			maptmp[tmp2]._root.erase(maptmp[tmp2]._root.find(";"));
			if (route.find("listing = false;") == std::string::npos && route.find("listing = true;") == std::string::npos)
			{
				std::cerr << "Config file: listing not found" << std::endl;
				exit(1);
			}
			if (route.find("listing = true;") != std::string::npos)
				maptmp[tmp2]._listing = true;
			else
				maptmp[tmp2]._listing = false;
			if (route.find("index =") == std::string::npos)
			{
				std::cerr << "Config file: index not found" << std::endl;
				exit(1);
			}
			maptmp[tmp2]._index = route.substr(route.find("index =") + 7, route.find(";", route.find("index =")) - route.find("index ="));
			maptmp[tmp2]._index.erase(maptmp[tmp2]._index.find(";"));
			maptmp[tmp2]._index = removespace(maptmp[tmp2]._index);
			// maptmp[tmp2]._index.erase(maptmp[tmp2]._index.find("/"));
			// maptmp[tmp2]._index.erase(maptmp[tmp2]._index.find_first_of("."));
			// maptmp[tmp2]._index.erase(maptmp[tmp2]._index.find(" "));
			if (route.find("cgi =") != std::string::npos)
			{
				//std::cerr << "Config file: cgi not found" << std::endl;
				maptmp[tmp2]._cgi = removespace(route.substr(route.find("cgi =") + 5, route.find(";", route.find("cgi =") - route.find("cgi ="))));
				maptmp[tmp2]._cgi.erase(maptmp[tmp2]._cgi.find(";"));
				//exit(1);
			}
			tmp.erase(0, tmp.find_first_of(")") + 1);
			res.push_back(maptmp);
			maptmp.clear();
			if (tmp.find_first_of(")") == std::string::npos)
			{
				tmp.clear();
				break;
			}
		}
		maptmp["NEXT"]._path = "true";
		res.push_back(maptmp);
		maptmp.clear();
	}
	return res;
}

int ServerConfig::checkdouble(std::string str, std::string tosearch, std::vector<std::map<std::string, std::string> > configs)
{
	for (std::vector<std::map<std::string, std::string> >::iterator it = configs.begin(); it != configs.end(); it++)
	{
		if (it->at(tosearch) == str)
			return 1;
	}
	return 0;
}
