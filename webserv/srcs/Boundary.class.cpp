/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boundary.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:21:47 by vgroux            #+#    #+#             */
/*   Updated: 2023/12/01 15:31:34 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boundary.class.hpp"

Boundary::Boundary()
{

}

Boundary::Boundary(const Boundary& src)
{
	(void)src;
}

Boundary& Boundary::operator=(const Boundary& src)
{
	(void)src;
	return (*this);
}
Boundary::~Boundary()
{

}

std::string	Boundary::getBody(void) const
{
	return (_body);
}

std::string	Boundary::getHeader(std::string key) const
{
	return (_headers.at(key));
}

void	Boundary::setHeader(std::string key, std::string value)
{
	_headers[key] = value;
}

void	Boundary::setBody(std::string body)
{
	_body = body;
}
