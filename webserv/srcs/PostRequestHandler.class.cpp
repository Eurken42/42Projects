/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequestHandler.class.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:10:16 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/19 14:36:58 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostRequestHandler.class.hpp"
#include <stdlib.h>

PostRequestHandler::PostRequestHandler(void)
{
	// std::cout << "PostRequestHandler default constructor called" << std::endl;
}

// PostRequestHandler::PostRequestHandler( CONFIG DU SERVER )
// {
// 	// std::cout << "PostRequestHandler default constructor called" << std::endl;
// 	// _conf = src._conf;
// }

PostRequestHandler::PostRequestHandler(const PostRequestHandler &src): RequestHandler(src)
{
	// std::cout << "Copy PostRequestHandler constructor called" << std::endl;
	if (this != &src)
	{
		// _conf = src._conf;
	}
}

PostRequestHandler&	PostRequestHandler::operator=(const PostRequestHandler &src)
{
	(void)src;
	return (*this);
}

PostRequestHandler::~PostRequestHandler(void)
{
}

void	PostRequestHandler::handlePostFile(HttpRequest *req)
{
	(void)req;
}

HttpRespond	PostRequestHandler::handleRequest(HttpRequest *req, Client *clt, Socket srv)
{
	(void)clt;
	(void)srv;
	HttpRespond	resp;
	if (req->isParsingDone() == false)
		std::cerr << "Le parsing de la requete a rencontre une erreur" << std::endl;
	else if (req->getPathRelative().empty())
	{
		std::cerr << "Le fichier/dossier n'existe pas ou les droits ne sont pas corrects" << std::endl;
		req->setErrorCode(404);
	}
	if (req->getErrorCode() == 0)
	{
		if (req->getPath().find(".php") == req->getPath().size() - 4)
		{
			std::string cgiresp;
			cgiresp = CgiExecutor::execute(clt, srv, "/usr/bin/php");
			if (cgiresp == "timeout")
			{
				resp.setStatus(502);
				resp.setBody(handleErrorPage(srv, resp.getStatus()));
			}
			else
			{
				resp.setBody(cgiresp);
				resp.setStatus(200);
			}
		}
		else if (req->isMultiform())
		{
			size_t start, end;
			std::string filecontent = req->getBody();
			std::string filename;
			chdir(srv.getDownload().c_str());
			start = filecontent.find("filename=");
			start += 10;
			end = filecontent.find_first_of('"', start);
			filename = filecontent.substr(start, end - start);
			std::string tmpname = filename;
			for (int i = 0; i < 100; i++)
			{
				int fd = open(tmpname.c_str(), O_RDONLY);
				if (fd != -1)
				{
					std::stringstream out;
					out << i;
					std::string prefix = out.str();
					prefix = "(" + prefix + ")";

					close(fd);
					if (i > 10)
						tmpname.erase(0, 5);
					else if (i > 0)
						tmpname.erase(0, 4);
					tmpname = prefix + tmpname;
				}
				else
				{
					filename = tmpname;
					break;
				}
			}
			filecontent.erase(0, end - start + 1);
			filecontent.erase(0, filecontent.find('\n') + 1);
			filecontent.erase(0, filecontent.find('\n') + 1);
			filecontent.erase(0, filecontent.find('\n') + 1);
			filecontent.erase(0, filecontent.find('\n') + 1);
			//filecontent.erase(filecontent.find(req->getBoundary()) - 2, req->getBoundary().length() + 4);
			std::ofstream result(filename);
			result << filecontent;
			result.close();
			chdir("../");
			req->setErrorCode(200);
			resp.setBody(openReadFile(req->getPath()));
			//exit(1);
		}	
	}
	else
	{
		/* GESTION ERREUR */
		resp.setStatus(req->getErrorCode());
		resp.setBody(handleErrorPage(srv, req->getErrorCode()));
	}
	resp.build(*req);
	return (resp);
}
