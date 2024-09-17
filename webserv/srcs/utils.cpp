/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:45:38 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/22 13:52:16 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string	getStatusStr(int statusCode)
{
	switch (statusCode)
	{
		case 100:
			return "Continue";
		case 101:
			return "Switching Protocol";
		case 200:
			return "OK";
		case 201:
			return "Created";
		case 202:
			return "Accepted";
		case 203:
			return "Non-Authoritative Information";
		case 204:
			return "No Content";
		case 205:
			return "Reset Content";
		case 206:
			return "Partial Content";
		case 300:
			return "Multiple Choice";
		case 301:
			return "Moved Permanently";
		case 302:
			return "Moved Temporarily";
		case 303:
			return "See Other";
		case 304:
			return "Not Modified";
		case 307:
			return "Temporary Redirect";
		case 308:
			return "Permanent Redirect";
		case 400:
			return "Bad Request";
		case 401:
			return "Unauthorized";
		case 403:
			return "Forbidden";
		case 404:
			return "Not Found";
		case 405:
			return "Method Not Allowed";
		case 406:
			return "Not Acceptable";
		case 407:
			return "Proxy Authentication Required";
		case 408:
			return "Request Timeout";
		case 409:
			return "Conflict";
		case 410:
			return "Gone";
		case 411:
			return "Length Required";
		case 412:
			return "Precondition Failed";
		case 413:
			return "Request Too Large";
		case 414:
			return "Request URI Too Long";
		case 415:
			return "Unsupported Media Type";
		case 416:
			return "Requested Range Not Satisfiable";
		case 417:
			return "Expectation Failed";
		case 418:
			return "I'm a teapot";
		case 421:
			return "Misdirected Request";
		case 425:
			return "Too Early";
		case 426:
			return "Upgrade Required";
		case 428:
			return "Precondition Required";
		case 429:
			return "Too Many Requests";
		case 431:
			return "Request Header Fields Too Large";
		case 451:
			return "Unavailable for Legal Reasons";
		case 500:
			return "Internal Server Error";
		case 501:
			return "Not Implemented";
		case 502:
			return "Bad Gateway";
		case 503:
			return "Service Unavailable";
		case 504:
			return "Gateway Timeout";
		case 505:
			return "HTTP Version Not Supported";
		case 506:
			return "Variant Also Negotiates";
		case 507:
			return "Insufficient Storage";
		case 510:
			return "Not Extended";
		case 511:
			return "Network Authentication Required";
		default:
			return "Undefined";
	}
}

std::string	toString(int i)
{
	std::stringstream ss;
    ss << i;
    return (ss.str());
}

std::string openReadFile(std::string relative_path)
{
	std::ifstream	file;
	std::string		result;
	std::ostringstream content;

	file.open(relative_path.c_str());
	if (file.is_open())
	{
		content << file.rdbuf();
		result = content.str();

		file.close();
	}
	else
		std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
	return result;
}

std::string openWriteFile(std::string relative_path)
{
	std::ifstream	file;
	std::string		result;
	std::ostringstream content;

	file.open(relative_path.c_str());
	if (file.is_open())
	{
		content << file.rdbuf();
		result = content.str();

		file.close();
	}
	else
		std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
	return result;
}

std::string	openReadCloseDir(std::string path, std::string uri)
{
	std::vector<std::pair<std::string, unsigned char> >	files;
	std::string					html;
	struct dirent	*ent;
	DIR *dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
			files.push_back(std::make_pair(ent->d_name, ent->d_type));
		closedir(dir);

		// Supprime le ./www/ au debut des url afin que les links fonctionnent.
		if (uri.find("./www/") != std::string::npos)
			uri.erase(uri.find("./www/"), uri.find("./www/") + 5);
		html = "<html><head><title>Index of " + path + "</title></head><body><h1>Index of " + uri + "</h1><hr>\n";
		if (uri.rfind('/') != uri.length() - 1)
			uri.append("/");
		for (std::vector<std::pair<std::string, unsigned char> >::iterator it = files.begin(); it < files.end(); it++)
		{
			if (it->first != "." && it->first != "..")
			{
				if (it->second == DT_DIR) // is a directory
					it->first.append("/");
				html += "<a href=\"" + it->first +  "\"" + "download>" + it->first + "</a><br>\n";
			}
		}
		html += "</hr>\n</body>\r</html>";
	}
	return (html);
}

