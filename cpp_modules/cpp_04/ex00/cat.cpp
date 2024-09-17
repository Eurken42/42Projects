/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/15 13:05:08 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.class.hpp"

Cat::Cat(void) {
	this->type = "Cat";
	std::cout << "Constructor Cat" << std::endl;
	return ;
}

Cat::Cat(const Cat& in) {
	std::cout << "Copy constructor Cat" << std::endl;
	*this = in;
	return ;
}

Cat::~Cat(void) {
	std::cout << "Destructor Cat" << std::endl;
	return ;
}

std::string Cat::getType(void) const {
	return this->type;
}

void Cat::setType(std::string type) {
	this->type = type;
}

void Cat::makeSound(void) const {
	std::cout << "Miaou" << std::endl;
}

Cat & Cat::operator = (const Cat& cat) {
	this->type = cat.getType();
	return *this;
}
