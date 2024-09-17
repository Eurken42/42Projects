/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequestHandler.class.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:06:16 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/18 13:45:25 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteRequestHandler.class.hpp"

DeleteRequestHandler::DeleteRequestHandler(void)
{
	// std::cout << "DeleteRequestHandler default constructor called" << std::endl;
}

// DeleteRequestHandler::DeleteRequestHandler( CONFIG DU SERVER )
// {
// 	// std::cout << "DeleteRequestHandler constructor called" << std::endl;
// 	// _conf = config;
// }

DeleteRequestHandler::DeleteRequestHandler(const DeleteRequestHandler &src): RequestHandler(src)
{
	// std::cout << "Copy DeleteRequestHandler constructor called" << std::endl;
	if (this != &src)
	{
		// _conf = src._conf;
	}
}

DeleteRequestHandler&	DeleteRequestHandler::operator=(const DeleteRequestHandler &src)
{
	// std::cout << "Assignement DeleteRequestHandler constructor called" << std::endl;
	// _conf = src._conf;
	(void)src;
	return (*this);
}

DeleteRequestHandler::~DeleteRequestHandler(void)
{
	// std::cout << "DeleteRequestHandler destructor called" << std::endl;
}

HttpRespond	DeleteRequestHandler::handleRequest(HttpRequest *req, Client *clt, Socket srv)
{
	HttpRespond	resp;
	int ret = 0;
	(void)clt;
	(void)srv;
	if (req->isParsingDone() == false)
		std::cerr << "Le parsing de la requete a rencontre une erreur" << std::endl;
	if (req->getErrorCode() == 0)
	{
		if (req->getPath().find(".php") == req->getPath().size() - 4)
		{
			std::string cgiresp;
			// std::cout << "entering cgi" << std::endl;
			cgiresp = CgiExecutor::execute(clt, srv, "/usr/bin/php");
			// std::cout << "CGI resp is : " << std::endl << cgiresp << std::endl;
			resp.setBody(cgiresp);
			resp.setStatus(200);
		}
		else
		{
			// std::cout << "L'HOMME METHODE DELETE" << std::endl;

			ret = std::remove(req->getPath().c_str());

			resp.setStatus(204);
		}
	}
	else
	{
		resp.setStatus(req->getErrorCode());
		resp.setBody(handleErrorPage(srv, req->getErrorCode()));
	}
	resp.build(*req);
	return (resp);
}
