#include "Client.hpp"

Client::Client() : _client_socket(-1)
{
	bzero(&_client, sizeof(_client));
	_clientsize = sizeof(_client);
	bzero(&_host, sizeof(_host));
	_clientnumber = -1;
	_last_msg = time(NULL);
	_bytesrcv = 0;
}

Client::~Client()
{

}

void Client::acceptConnection(int listeningsocket, int nbclient, fd_set *readset, std::list<Client> *clientlist, int port)
{
	bzero(&_client, sizeof(_client));
	_clientsize = sizeof(_client);
	std::list<Client>::iterator it2;
	(void)nbclient;
	// if (nbclient >= 1024)
	// {
	// 	std::cout << "SERVER FULL" << std::endl;
	// 	_client_socket = -1;
	// 	return;
	// }

	_client_socket = accept(listeningsocket, (sockaddr *)&_client, (socklen_t *)&_clientsize);

	if (_client_socket < 0 || fcntl(_client_socket, F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0)
	{
		close(_client_socket);
		_client_socket = -1;
		return;
	}
	_serversocket = listeningsocket;
	_port = port;
	(void)clientlist;
	// for(std::list<Client>::iterator it = clientlist->begin(); it != clientlist->end(); it++)
	// {
	// 	it2 = it;
	// 	if (_client_socket == it->_client_socket && (++it2) != clientlist->end())
	// 	{
	// 		clientlist->erase(it);
	// 		break;
	// 	}
	// }
	(void)readset;
}

void Client::checknewconnection(std::list<Client> * clientlist)
{
	static int i = 0;
	if (clientlist->back()._client_socket != -1)
	{
		clientlist->back()._clientnumber = ++i;
		std::cout << "Client [" << clientlist->back()._clientnumber << "] has been connected on port " << clientlist->back()._port << std::endl;
		std::cout << clientlist->size() << " Client actually connected with socket: " << clientlist->back()._client_socket << std::endl;
		clientlist->push_back(Client());
	}
}
