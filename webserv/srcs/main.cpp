/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:07:46 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/22 13:54:37 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
//#include "Socket.hpp"

int main( int ac,char **av)
{
	ServerConfig configuration;
	Socket *serverarray = NULL;
	
	if (ac == 1)
		serverarray = ServerConfig::parsefile("configs/default.UDC");
	else if (ac == 2)
		serverarray = ServerConfig::parsefile(av[1]);
	else
	{
		std::cerr << "Usage: ./webserv CONFIG_FILE.UDC" << std::endl;
		exit(1);
	}
	std::list<Client> clientlist;
	clientlist.push_back(Client());
	//Socket::setup(serverarray);
	for (int i = 0; i < serverarray[0].getTotalServ(); i++)
	{
		serverarray[i].setListening(Socket::getListenSock(serverarray[i]._config));
		//std::cout << "server on port " << serverarray[i].getPort() << " downloads to " << serverarray[i].getDownload() << std::endl;
	}
	Socket::handleConnection(&clientlist, serverarray);
	delete [] serverarray;
	return 0;
}
