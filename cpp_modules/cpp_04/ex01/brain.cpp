/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 14:56:48 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.class.hpp"

Brain::Brain(void) {
	std::cout << "Constructor Brain" << std::endl;
	return ;
}

Brain::Brain(const Brain& in) {
	std::cout << "Copy constructor Brain" << std::endl;
	*this = in;
	return ;
}

Brain::~Brain(void) {
	std::cout << "Destructor Brain" << std::endl;
	return ;
}
