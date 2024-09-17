/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRespond.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:11:18 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/17 14:38:18 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRespond.class.hpp"

HttpRespond::HttpRespond(void)
{
	_status_code = 0;
	(void)_headers;
	_body = "";
	_isBuilt = false;
}

HttpRespond::~HttpRespond(void)
{

}

std::string	HttpRespond::generateStatusLine(void)
{
	std::string	resp;
	resp = "HTTP/1.1 " + toString(_status_code) + " " + getStatusStr(_status_code) + "\r\n";
	return (resp);
}

std::string	HttpRespond::generateHeaders(void)
{
	std::string	heads;
	
	setHeader("Content-Length", toString(_body.length() + 2));
	for (std::map<std::string, std::string>::const_iterator i = _headers.begin(); i != _headers.end(); i++)
		heads += i->first + ": " + i->second + "\r\n";
	heads += "\r\n";
	return (heads);
}

std::string	getDate(void)
{
	char buffer[1000];
    time_t now = time(0);
    struct tm *timeinfo = gmtime(&now);

    strftime(buffer, 1000, "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
    return buffer;
}

bool HttpRespond::build(HttpRequest req)
{
	std::string	path = req.getPath();
	_isBuilt = false;
	setHeader("Date", getDate());
	// setHeader("Connection", req.getHeader("connection"));

	if (path.find(".png") != std::string::npos)
		setHeader("Content-Type", "image/png");
	else if (path.find(".jpg") != std::string::npos || path.find(".jpeg") != std::string::npos)
		setHeader("Content-Type", "image/jpeg");
	else if (path.find(".ico") != std::string::npos)
		setHeader("Content-Type", "image/x-icon");
	else if (path.find(".css") != std::string::npos)
		setHeader("Content-Type", "text/css");
	else if (_body.length() != 0)
		setHeader("Content-Type", "text/html; charset=UTF-8");
	if (req.getErrorCode() == 0)
		_status_code = 200;
	else if (req.getErrorCode() == 408)
	{
		setHeader("Connection", "close");
	}
	else
	{
		_status_code = req.getErrorCode();
		if (_body.empty())
		{
			_body = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>body {font-family: 'Arial', sans-serif;background-color: #f7f7f7;margin: 0;padding: 0;display: flex;align-items: center;justify-content: center;height: 100vh;}.error-container{text-align:center;padding:20px;background-color:#fff;border-radius:8px;box-shadow: 0 4px 8px rgba(0,0,0,0.1);}h1{color:#e44d26;font-size:3em;margin-bottom:10px;}p{color:#333;font-size:1.2em;margin-bottom:20px;}a{color:#0275d8;text-decoration:none;}a:hover{text-decoration:underline;}</style><title>";
			_body += req.getErrorCode();
			_body.append(" - ");
			_body.append(getStatusStr(_status_code));
			_body.append("</title></head><body><div class=\"error-container\"><h1>");
			_body += req.getErrorCode();
			_body.append(" - ");
			_body.append(getStatusStr(_status_code));
			_body.append("</h1><p>Oops! Something goes wrong.</p><p>Return to <a href=\"/\">home</a>.</p></div></body></html>");
		}
	}
	_body += "\r\n";
	_resp = generateStatusLine();
	_resp += generateHeaders();
	_resp += "\r\n" + _body;
	_isBuilt = true;
	return (true);
}

bool HttpRespond::isBuild(void)
{
	return (_isBuilt);
}

int	HttpRespond::getStatus(void)
{
	return (_status_code);
}

std::string	HttpRespond::getHeader(std::string key)
{
	return (_headers.at(key));
}

std::map<std::string, std::string>	HttpRespond::getHeaders(void)
{
	return (_headers);
}

std::string	HttpRespond::getBody(void)
{
	return (_body);
}

std::string	HttpRespond::getResp(void)
{
	if (_isBuilt == false)
		return ("");
	return (_resp);
}

void	HttpRespond::setStatus(int status)
{
	_status_code = status;
}

void	HttpRespond::setHeader(std::string key, std::string value)
{
	_headers[key] = value;
}

void	HttpRespond::setBody(std::string body)
{
	_body = body;
}
