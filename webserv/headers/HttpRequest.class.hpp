/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:09:38 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/19 15:36:39 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_CLASS_HPP
# define HTTPREQUEST_CLASS_HPP

# include <iostream>
# include <cstring>
# include <sstream>
# include <map>
# include <vector>
# include <cstring>
# include <string.h>
# include "Boundary.class.hpp"

# ifndef URI_MAX_LEN
#  define URI_MAX_LEN 4096
# endif

enum HttpMethod
{
	GET,
	POST,
	DELETE,
	NONE
};

enum ParsingState
{
	REQUEST_LINE,
	REQUEST_LINE_METHOD,
	REQUEST_LINE_SPACE_BEFORE_URI,
	REQUEST_LINE_URI_SLASH,
	REQUEST_LINE_URI,
	REQUEST_LINE_URI_QUERY,
	REQUEST_LINE_URI_FRAGMENT,
	REQUEST_LINE_SPACE_AFTER_URI,
	REQUEST_LINE_H,
	REQUEST_LINE_HT,
	REQUEST_LINE_HTT,
	REQUEST_LINE_HTTP,
	REQUEST_LINE_HTTP_SLASH,
	REQUEST_LINE_MAJOR_DIGIT,
	REQUEST_LINE_DOT,
	REQUEST_LINE_MINOR_DIGIT,
	REQUEST_LINE_CR,
	REQUEST_LINE_LF,
	FIELDS_START,
	FIELDS_KEY,
	FIELDS_VALUE,
	FIELDS_VALUE_END,
	FIELDS_END,
	CHUNKED_LENGTH_BEGIN,
	CHUNKED_LENGTH,
	CHUNKED_LEN_CR,
	CHUNKED_LEN_LF,
	CHUNKED_DATA,
	CHUNKED_DATA_CR,
	CHUNKED_DATA_LF,
	CHUNKED_END_CR,
	CHUNKED_END_LF,
	BODY,
	PARSING_DONE
};

class HttpRequest
{
	private:
		HttpMethod							_method;
		std::map<HttpMethod, std::string>	_method_str;
		std::map<std::string, std::string>	_headers;
		std::vector<unsigned char>			_body;
		std::string							_body_str;
		std::string							_path;
		std::string							_query;
		std::string							_fragment;
		std::string							_conn;
		std::string							_server_name;
		std::string							_boundary;
		std::vector<Boundary>				_bounded;
		std::string							_path_relative;
		bool								_isDir;
		bool								_fields_done;
		bool								_body_exist;
		bool								_chunked;
		bool								_multiform;
		bool								_keep_alive;
		size_t								_body_len;
		int									_err_code;
		unsigned int						_ver_maj;
		unsigned int						_ver_min;
		ParsingState						_state;

		void								_handleHeaders(void);
		void								_handleBoundary(void);

	public:
		HttpRequest();
		HttpRequest(const HttpRequest& src);
		HttpRequest& operator=(const HttpRequest& src);
		~HttpRequest();

		HttpMethod							getMethod(void) const;
		std::string							getMethodStr(void) const;
		std::string							getPath(void) const;
		std::string							getServerName(void) const;
		std::string							getQuery(void) const;
		std::string							getFragment(void) const;
		std::string							getHeader(std::string const &name) const;
		std::map<std::string, std::string>	getHeaders(void) const;
		std::string							getBody(void) const;
		std::string							getBoundary(void) const;
		std::string							getPathRelative(void) const;
		int									getErrorCode(void) const;
		std::vector<Boundary>				getBounded(void) const;

		bool	isDirectory(void) const;
		bool	isMultiform(void) const;
		bool	isParsingDone(void) const;
		bool	keepAlive(void) const;

		void	printMessage(void) const;
		void	setPathRelative(std::string &str);
		void	setPath(std::string &str);
		void	setHeader(std::string key, std::string value);
		void	setDirectory(bool b);
		void	setErrorCode(int x);
		void	setKeepAlive(bool b);
		void	setParsing(ParsingState ps);
		void	parse(const char *data, size_t len, int maxBody);
		void	resetRequest(void);
};

#endif
