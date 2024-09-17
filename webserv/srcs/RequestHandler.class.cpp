/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:02:28 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/22 13:50:03 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHandler.class.hpp"

RequestHandler::RequestHandler(void)
{
	// std::cout << "RequestHandler default constructor called" << std::endl;
}

RequestHandler::RequestHandler(const RequestHandler& src)
{
	// std::cout << "Copy RequestHandler constructor called" << std::endl;
	if (this != &src)
	{
		// _config = src._config;
	}
}

RequestHandler&	RequestHandler::operator=(const RequestHandler& src)
{
	// std::cout << "Assignement RequestHandler constructor called" << std::endl;
	// _config = src._config;
	(void)src;
	return (*this);
}

RequestHandler::~RequestHandler(void)
{
	// std::cout << "RequestHandler destructor called" << std::endl;
}

std::string RequestHandler::handleErrorPage(Socket srv, int errCode)
{
	std::string	errfile;
	
	errfile = srv._error + toString(errCode) + ".html";

	if (openReadFile(errfile).empty())
		errfile = "./errfile/" + toString(errCode) + ".html";
	if (openReadFile(errfile).empty())
	{
		std::string	str;
		str = "<html><head><style type=text/css>p {color:blue; font-weight:900; font-size:20px; font-family:Helvetica,Arial,sans-serif; }</style></head><body><p>ERROR ";
		str += toString(errCode) + " " + getStatusStr(errCode) + "</p><p>The serveur has timeout</p></body></html>";
		return (str);
	}
	return (openReadFile(errfile));
}
