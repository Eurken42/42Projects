/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boundary.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:12:52 by vgroux            #+#    #+#             */
/*   Updated: 2023/12/01 15:30:14 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUNDARY_CLASS_HPP
# define BOUNDARY_CLASS_HPP

# include <iostream>
# include <map>

class Boundary
{
	private:
		std::map<std::string, std::string>	_headers;
		std::string							_body;

	public:
		Boundary();
		Boundary(const Boundary& src);
		Boundary& operator=(const Boundary& src);
		~Boundary();

		std::string	getHeader(std::string key) const;
		std::string	getBody(void) const;

		void	setHeader(std::string key, std::string value);
		void	setBody(std::string body);
};

#endif
