/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:09:14 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/22 14:54:44 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.class.hpp"

HttpRequest::HttpRequest(void)
{
	// std::cout << "HttpRequest Default constructor called" << std::endl;
	_method_str[::GET] = "GET";
	_method_str[::POST] = "POST";
	_method_str[::DELETE] = "DELETE";
	_method_str[::NONE] = "NONE";
	resetRequest();
	return ;
}

HttpRequest::HttpRequest(const HttpRequest& src)
{
	// std::cout << "HttpRequest Copy constructor called" << std::endl;
	if (this != &src)
	{
		_method = src._method;
		_method_str = src._method_str;
		_headers = src._headers;
		_body = src._body;
		_body_str = src._body_str;
		_path = src._path;
		_query = src._query;
		_fragment = src._fragment;
		_conn = src._conn;
		_server_name = src._server_name;
		_boundary = src._boundary;
		_fields_done = src._fields_done;
		_body_exist = src._body_exist;
		_chunked = src._chunked;
		_multiform = src._multiform;
		_body_len = src._body_len;
		_err_code = src._err_code;
		_ver_maj = src._ver_maj;
		_ver_min = src._ver_min;
		_state = src._state;
	}
	return ;
}

HttpRequest&	HttpRequest::operator=(const HttpRequest& src)
{
	// std::cout << "HttpRequest Assignement constructor called" << std::endl;
	if (this != &src)
	{
		_method = src._method;
		_method_str = src._method_str;
		_headers = src._headers;
		_body = src._body;
		_body_str = src._body_str;
		_path = src._path;
		_query = src._query;
		_fragment = src._fragment;
		_conn = src._conn;
		_server_name = src._server_name;
		_boundary = src._boundary;
		_fields_done = src._fields_done;
		_body_exist = src._body_exist;
		_chunked = src._chunked;
		_multiform = src._multiform;
		_body_len = src._body_len;
		_err_code = src._err_code;
		_ver_maj = src._ver_maj;
		_ver_min = src._ver_min;
		_state = src._state;
	}
	return *this;
}

HttpRequest::~HttpRequest(void)
{
	// std::cout << "HttpRequest Destructor called" << std::endl;
	resetRequest();
}

bool    allowedCharURI(char c)
{
	if ((c >= '#' && c <= ';') || (c >= '?' && c <= '[') || (c >= 'a' && c <= 'z') ||
	   c == '!' || c == '=' || c == ']' || c == '_' || c == '~')
		return (true);
	return (false);
}

bool	checkUriPath(std::string _path)
{
	char	*tmp = strtok((char *)_path.c_str(), "/");
	int		pos = 0;

	while (tmp != NULL)
	{
		if (!strcmp(tmp, ".."))
			pos--;
		else
			pos++;
		if (pos < 0)
			return (false);
		tmp = strtok(NULL, "/");
	}
	return true;
}

HttpMethod	HttpRequest::getMethod(void) const
{
	return _method;
}

std::string	HttpRequest::getMethodStr(void) const
{
	return _method_str.at(_method);
}

std::string	HttpRequest::getPath(void) const
{
	return _path;
}

int HttpRequest::getErrorCode(void) const
{
	return _err_code;
}

std::string HttpRequest::getServerName(void) const
{
	return _server_name;
}

std::string HttpRequest::getQuery(void) const
{
	return _query;
}

std::string HttpRequest::getFragment(void) const
{
	return _fragment;
}

std::string HttpRequest::getHeader(std::string const &name) const
{
	if (_headers.count(name) != 0)
		return _headers.at(name);
	else
		return "";
}

std::map<std::string, std::string> HttpRequest::getHeaders(void) const
{
	return _headers;
}

std::string HttpRequest::getBody(void) const
{
	return _body_str;
}

std::string	HttpRequest::getBoundary(void) const
{
	return _boundary;
}

std::string HttpRequest::getPathRelative(void) const
{
	return this->_path_relative;
}

std::vector<Boundary>	HttpRequest::getBounded(void) const
{
	return (_bounded);
}

bool	HttpRequest::isDirectory(void) const
{
	return _isDir;
}

void	HttpRequest::setDirectory(bool b)
{
	_isDir = b;
}

void HttpRequest::setPathRelative(std::string &str)
{
	this->_path_relative = str;
}

void HttpRequest::setPath(std::string &str)
{
	this->_path = str;
}


void HttpRequest::setErrorCode(int x)
{
	if (x < 0 || x > 600)
		_err_code = 0;
	else
		_err_code = x;
}

void	HttpRequest::setParsing(ParsingState ps)
{
	_state = ps;
}

bool HttpRequest::isMultiform(void) const
{
	return _multiform;
}

bool HttpRequest::isParsingDone(void) const
{
	if (_state == PARSING_DONE)
		return true;
	else
		return false;
}

bool	HttpRequest::keepAlive(void) const
{
	return (_keep_alive);
}

void	HttpRequest::printMessage(void) const
{
	std::cout << "HttpRequest with:" << std::endl;
	std::cout << "Method\t" << _method_str.at(_method) << "\tHTTP/" << _ver_maj << "." << _ver_min << std::endl;
	std::cout << "Path\t\t" << _path << std::endl;
	std::cout << "Rel_Path\t" << _path_relative << std::endl;
	std::cout << "Query\t\t" << _query << std::endl;
	std::cout << "Fragment\t" << _fragment << std::endl;
	std::cout << "ServerName\t" << _server_name << std::endl;
	std::cout << "ErrorCode\t" << _err_code << std::endl;
	std::cout << "ParserState\t" << _state << std::endl;
	std::cout << "Boundary\t" << _boundary << "\tMultiform\t" << _multiform << std::endl;

	std::cout << std::endl << "--- HEADERS ---" << std::endl;
	for (std::map<std::string, std::string>::const_iterator i = _headers.begin(); i != _headers.end(); i++)
		std::cout << i->first + "--" + i->second << std::endl;

	std::cout << "--- BODY ---" << std::endl;
	for (std::vector<unsigned char>::const_iterator i = _body.begin(); i != _body.end(); i++)
		std::cout << *i;
	std::cout <<"--- END OF BODY ---" << std::endl;
}

void	HttpRequest::setHeader(std::string key, std::string value)
{
	// key to lower
	for (size_t i = 0; i < key.length(); i++)
		key[i] = std::tolower(key[i]);

	// trim spaces before and after the value
	value.erase(0, value.find_first_not_of(" \t"));
	value.erase(value.find_last_not_of(" \t") + 1);
	
	_headers[key] = value;
}

void	HttpRequest::parse(const char *data, size_t len, int maxBody)
{
	char				c;
	short				mi = 1;
	int					chunk_len = 0;
	std::stringstream	s;
	std::string			temp;
	std::string			tmp;

	resetRequest();
	if (strlen(data) == 0)
	{
		std::cerr << "data buff emtpy" << std::endl;
		return ;
	}
	for (size_t i = 0; i <= len; i++)
	{
		c = data[i];
		switch(_state)
		{
			case REQUEST_LINE:
			{
				if (c == 'G')
					_method = GET;
				else if (c == 'P')
					_method = POST;
				else if (c == 'D')
					_method = DELETE;
				else
				{
					_err_code = 501;
					std::cerr << "Method Error in REQUEST_LINE. char is: " << c << std::endl;
					return ;
				}
				_state = REQUEST_LINE_METHOD;
				break ;
			}
			case REQUEST_LINE_METHOD:
			{
				if (c == _method_str[_method][mi])
					mi++;
				else
				{
					_err_code = 501;
					std::cerr << "Method Error in REQUEST_LINE_METHOD. char is: " << c << std::endl;
					return ;
				}

				if ((size_t)mi == _method_str[_method].length())
					_state = REQUEST_LINE_SPACE_BEFORE_URI;
				break ;
			}
			case REQUEST_LINE_SPACE_BEFORE_URI:
			{
				if (c != ' ')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_SPACE_BEFORE_URI)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_URI_SLASH;
				break ;
			}
			case REQUEST_LINE_URI_SLASH:
			{
				if (c == '/')
				{
					_state = REQUEST_LINE_URI;
					temp.clear();
				}
				else
				{
					_err_code = 400;
					std::cerr << "Bad request (REQUEST_LINE_URI_SLASH)" << std::endl;
				}
				break ;
			}
			case REQUEST_LINE_URI:
			{
				if (c == ' ')
				{
					_path.append(temp);
					temp.clear();
					_state = REQUEST_LINE_H;
					continue ;
				}
				else if (c == '?')
				{
					_path.append(temp);
					temp.clear();
					_state = REQUEST_LINE_URI_QUERY;
					continue ;
				}
				else if (c == '#')
				{
					_path.append(temp);
					temp.clear();
					_state = REQUEST_LINE_URI_FRAGMENT;
					continue ;
				}
				else if (!allowedCharURI(c))
				{
					_err_code = 400;
					std::cerr << "Bad request (REQUEST_LINE_URI)" << std::endl;
					return ;
				}
				else if (i > URI_MAX_LEN)
				{
					_err_code = 414;
					std::cerr << "URI Too Long (REQUEST_LINE_URI)" << std::endl;
					return ;
				}
				break ;
			}
			case REQUEST_LINE_URI_QUERY:
			{
				if (c == ' ')
				{
					_query.append(temp);
					temp.clear();
					_state = REQUEST_LINE_H;
					continue ;
				}
				else if (c == '#')
				{
					_query.append(temp);
					temp.clear();
					_state = REQUEST_LINE_URI_FRAGMENT;
					continue ;
				}
				else if (!allowedCharURI(c))
				{
					_err_code = 400;
					std::cerr << "Bad request (REQUEST_LINE_URI_QUERY)" << std::endl;
					return ;
				}
				else if (i > URI_MAX_LEN)
				{
					_err_code = 414;
					std::cerr << "URI Too Long (REQUEST_LINE_URI_QUERY)" << std::endl;
					return ;
				}
				break ;
			}
			case REQUEST_LINE_URI_FRAGMENT:
			{
				if (c == ' ')
				{
					_fragment.append(temp);
					temp.clear();
					_state = REQUEST_LINE_H ;
					continue ;
				}
				else if (!allowedCharURI(c))
				{
					_err_code = 400;
					std::cerr << "Bad request (REQUEST_LINE_URI_FRAGMENT)" << std::endl;
					return ;
				}
				else if (i > URI_MAX_LEN)
				{
					_err_code = 414;
					std::cerr << "URI Too Long (REQUEST_LINE_URI_FRAGMENT)" << std::endl;
					return ;
				}
				break ;
			}
			case REQUEST_LINE_SPACE_AFTER_URI:
			{
				if (c == ' ')
					_state = REQUEST_LINE_H;
				else
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_SPACE_AFTER_URI" << std::endl;
					return ;
				}
				break ;
			}
			case REQUEST_LINE_H:
			{
				if (c != 'H')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_H)" << std::endl;
					return ;
				}
				else if (!checkUriPath(_path))
				{
					_err_code = 400;
					std::cerr << "Request URI Error (REQUEST_LINE_H)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_HT;
				break;
			}
			case REQUEST_LINE_HT:
			{
				if (c != 'T')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_HT)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_HTT;
				break ;
			}
			case REQUEST_LINE_HTT:
			{
				if (c != 'T')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_HTT)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_HTTP;
				break ;
			}
			case REQUEST_LINE_HTTP:
			{
				if (c != 'P')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_HTTP)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_HTTP_SLASH;
				break ;
			}
			case REQUEST_LINE_HTTP_SLASH:
			{
				if (c != '/')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_HTTP_SLASH)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_MAJOR_DIGIT;
				break ;
			}
			case REQUEST_LINE_MAJOR_DIGIT:
			{
				if (!isdigit(c))
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_MAJOR_DIGIT)" << std::endl;
					return ;
				}
				if (c != '1')
				{
					_err_code = 505;
					std::cerr << "HTTP Version Not Supported" << std::endl;
					return ;
				}
				_ver_maj = c - '0';
				_state = REQUEST_LINE_DOT;
				break ;
			}
			case REQUEST_LINE_DOT:
			{
				if (c != '.')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_DOT)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_MINOR_DIGIT;
				break ;
			}
			case REQUEST_LINE_MINOR_DIGIT:
			{
				if (!isdigit(c))
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_MINOR_DIGIT)" << std::endl;
					return ;
				}
				if (c != '1')
				{
					_err_code = 505;
					std::cerr << "HTTP Version Not Supported" << std::endl;
					return ;
				}
				_ver_min = c - '0';
				_state = REQUEST_LINE_CR;
				break ;
			}
			case REQUEST_LINE_CR:
			{
				if (c != '\r')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_CR)";
					return ;
				}
				_state = REQUEST_LINE_LF;
				break ;
			}
			case REQUEST_LINE_LF:
			{
				if (c != '\n')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_LF)" << std::endl;
					return ;
				}
				_state = FIELDS_START;
				break ;
			}
			case FIELDS_START:
			{
				temp.clear();
				if (c == '\r')
					_state = FIELDS_END;
				else if (isalpha(c) || c == '_')
					_state = FIELDS_KEY;
				else
				{
					_err_code = 400;
					std::cerr << "Bad Request (FIELDS_START)" << std::endl;
					return ;
				}
				break ;
			}
			case FIELDS_KEY:
			{
				if (c == ':')
				{
					tmp.clear();
					tmp = temp; // tmp devient la clé
					temp.clear();
					_state = FIELDS_VALUE;
					continue ;
				}
				else if (!isalpha(c) && c != '-')
				{
					_err_code = 400;
					std::cerr << "Bad Request (FIELDS_KEY) and char is " << c << std::endl;
					return ;
				}
				break ;
			}
			case FIELDS_VALUE:
			{
				if (c == '\r')
				{
					setHeader(tmp, temp); // tmp = key | temp = value
					tmp.clear();
					temp.clear();
					_state = FIELDS_VALUE_END;
					continue ;
				}
				break ;
			}
			case FIELDS_VALUE_END:
			{
				if (c == '\n')
				{
					_state = FIELDS_START;
					continue ;
				}
				else
				{
					_err_code = 400;
					std::cerr << "Bad Request (FIELDS_VALUE_END)" << std::endl;
					return ;
				}
				break ;
			}
			case FIELDS_END:
			{
				if (c == '\n')
				{
					temp.clear();
					_fields_done = true;
					if (_headers.count("content-length") && _headers.count("transfer-encoding") && _headers["transfer-encoding"].find_first_of("chunked") != std::string::npos)
					{
						_err_code = 400;
						std::cerr << "Bad Request (Transfer-Encoding: Chunked + Content-Length)" << std::endl;
						return ;
					}
					_handleHeaders();
					if (_server_name == "")
					{
						_err_code = 400;
						std::cerr << "Bad Request (Doesn't have the Host header)" << std::endl;
						return ;
					}
					if (_method == POST && _body_len == 0 && _chunked == false)
					{
						_err_code = 411;
						std::cerr << "ERROR: Lenght required" << std::endl;
						return ;
					}
					if (_body_exist)
					{
						if (_chunked)
							_state = CHUNKED_LENGTH_BEGIN;
						else
							_state = BODY;
					}
					else
						_state = PARSING_DONE;
				}
				else
				{
					_err_code = 400;
					std::cerr << "Bad Request (FIELDS_END)" << std::endl;
					return ;
				}
				break ;
			}
			case CHUNKED_LENGTH_BEGIN:
			{
				if (!isxdigit(c))
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_LENGTH_BEGIN)" << std::endl;
					return ;
				}
				chunk_len = 0;
				s.str("");
				s.clear();
				s << c;
				s >> std::hex >> chunk_len;
				if (chunk_len == 0)
					_state = CHUNKED_LEN_CR;
				else
					_state = CHUNKED_LENGTH;
				break ;
			}
			case CHUNKED_LENGTH:
			{
				if (isxdigit(c))
				{
					mi = 0;
					s.str("");
					s.clear();
					s << c;
					s >> std::hex >> mi;
					chunk_len *= 16;
					chunk_len += mi;
				}
				else if (c == '\r')
					_state = CHUNKED_LEN_LF;
				else
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_LENGTH)" << std::endl;
					return ;
				}
				break ;
			}
			case CHUNKED_LEN_CR:
			{
				if (c != '\r')
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_CR)" << std::endl;
					return ;
				}
				_state = CHUNKED_LEN_LF;
				break ;
			}
			case CHUNKED_LEN_LF:
			{
				if (c != '\n')
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_LF)" << std::endl;
					return ;
				}
				if (chunk_len == 0)
					_state = CHUNKED_END_CR;
				else
					_state = CHUNKED_DATA;
				break ;
			}
			case CHUNKED_DATA:
			{
				_body.push_back(c);
				chunk_len--;
				if (chunk_len == 0)
					_state = CHUNKED_DATA_CR;
				break ;
			}
			case CHUNKED_DATA_CR:
			{
				if (c != '\r')
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_DATA_CR)" << std::endl;
					return ;
				}
				_state = CHUNKED_DATA_LF;
				break ;
			}
			case CHUNKED_DATA_LF:
			{
				if (c != '\n')
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_DATA_LF)" << std::endl;
					return ;
				}
				_state = CHUNKED_LENGTH_BEGIN;
				break ;
			}
			case CHUNKED_END_CR:
			{
				if (c != '\r')
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_END_CR)" << std::endl;
					return ;
				}
				_state = CHUNKED_END_LF;
				break ;
			}
			case CHUNKED_END_LF:
			{
				if (c != '\n')
				{
					_err_code = 400;
					std::cerr << "Bad Request (CHUNKED_END_LF)" << std::endl;
					return ;
				}
				_state = PARSING_DONE;
				break ;
			}
			case BODY:
			{
				if (_body.size() > (unsigned long)maxBody)
				{
					_err_code = 413;
					std::cerr << "ERROR WHEN PARSING THE REQUEST (BODY)" << std::endl;
					return ;
				}
				if (_body.size() < _body_len)
				{
					_body.push_back(c);
					_body_str += c;
				}
				if (_body.size() == _body_len)
					_state = PARSING_DONE;
				break ;
			}
			case PARSING_DONE:
			{
				return ;
			}
		}
		temp += c;
	}
	if (_state == PARSING_DONE)
	{
		if (_multiform)
			{
				_body_str.append((char *)_body.data(), _body.size());
				//_handleBoundary();
			}
		else
			_body_str.append((char *)_body.data(), _body.size());
	}
}

void	HttpRequest::_handleHeaders(void)
{
	std::stringstream	s;

	if (_headers.count("content-length"))
	{
		_body_exist = true;
		s << _headers["content-length"];
		s >> _body_len;
	}
	else if (_headers.count("transfer-encoding"))
	{
		_body_exist = true;
		_chunked = true;
	}
	if (_headers.count("host"))
	{
		size_t	end = _headers["host"].find_first_of(":");
		_server_name = _headers["host"].substr(0, end);
	}
	if (_headers.count("content-type") && _headers["content-type"].find("multipart/form-data") != std::string::npos)
	{
		size_t	pos = _headers["content-type"].find("boundary=");
		if (pos != std::string::npos)
			_boundary = _headers["content-type"].substr(pos + 9, _headers["content-type"].size());
		_multiform = true;
	}
	if (_headers.count("connection"))
	{
		if (_headers["connection"] == "keep-alive")
			_keep_alive = true;
	}
}

void	HttpRequest::resetRequest(void)
{
	_method = NONE;
	_headers.clear();
	_body.clear();
	_body_str.clear();
	_path.clear();
	_path = "./www";
	_query.clear();
	_fragment.clear();
	_conn.clear();
	_server_name.clear();
	_boundary.clear();
	_path_relative.clear();
	_fields_done = false;
	_body_exist = false;
	_chunked = false;
	_multiform = false;
	_isDir = false;
	_keep_alive = false;
	_body_len = 0;
	_err_code = 0;
	_ver_maj = 0;
	_ver_min = 0;
	_state = REQUEST_LINE;
}

void	HttpRequest::setKeepAlive(bool b)
{
	_keep_alive = b;
}

void	HttpRequest::_handleBoundary(void)
{
	// std::cout << "HANDLE BOUNDARY" << std::endl;
	std::string	body = _body_str;
	std::string	tmp;
	size_t		begin = 0;
	size_t		end = 0;

	begin = body.find("--" + _boundary);
	end = body.find("--" + _boundary, begin + _boundary.length());
	while (end != std::string::npos)
	{
		Boundary	bound;
		tmp = body.substr(begin, end);
		tmp.erase(end, end + _boundary.length() + 2);
		tmp.erase(begin, begin + _boundary.length() + 2);
		tmp.erase(0, 2);
		tmp.erase(tmp.length() - 2);

		std::istringstream	sstr(tmp);
		std::string			line;
		std::getline(sstr, line);
		while (line.compare("\r\n") != 0)
		{
			// std::cout << "LINE=\"" << line << "\"" << std::endl << "TMP=\"" << tmp << "\"" << std::endl;
			std::string	key;
			std::string	value;
			size_t		delim = line.find_first_of(':');
			key = line.substr(0, delim);
			value = line.substr(delim + 2);

			// std::cout << "key= \"" << key << "\"\tvalue= \"" << value << "\"" << std::endl;

			bound.setHeader(key, value);
			std::getline(sstr, line);
		}

		begin = body.find("--" + _boundary, end);
		end = (body.find("--" + _boundary, begin + _boundary.length()));
		// std::cout << begin << std::endl;
		// std::cout << end << std::endl;
	}
}
