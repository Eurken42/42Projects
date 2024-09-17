/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:59:08 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/06 16:12:25 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_CLASS_HPP
# define EASYFIND_CLASS_HPP

#include <iostream>
#include <list>

template<typename T>
void easyfind(T const& x, int y) {
	std::list<int>::const_iterator it;
	std::list<int>::const_iterator ite = x.end();

	for (it = x.begin(); it != ite; ++it) {
		if (*it == y) {
			std::cout << "Found ! :D" << std::endl;
			break ;
		}
	}
	if (it == ite)
		std::cout << "Not found !" << std::endl;
}

#endif
