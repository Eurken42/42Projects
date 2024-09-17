/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRespond.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:55:44 by vgroux            #+#    #+#             */
/*   Updated: 2023/12/01 15:08:07 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPOND_CLASS_HPP
# define HTTP_RESPOND_CLASS_HPP

# include "HttpRequest.class.hpp"
# include "utils.hpp"
# include <iostream>
# include <string>
# include <sstream>
# include <map>
# include <ctime>

class HttpRespond
{
	private:
		int									_status_code;
		std::map<std::string, std::string>	_headers;
		std::string							_body;
		bool								_isBuilt;
		std::string							_resp;

		std::string	generateStatusLine(void);
		std::string	generateHeaders(void);

	public:
		HttpRespond(void);
		~HttpRespond(void);

		bool	build(HttpRequest req);
		bool	isBuild(void);

		int									getStatus(void);
		std::string							getHeader(std::string key);
		std::map<std::string, std::string>	getHeaders(void);
		std::string							getBody(void);
		std::string							getResp(void);

		void	setStatus(int status);
		void	setHeader(std::string key, std::string value);
		void	setBody(std::string body);
};

#endif
