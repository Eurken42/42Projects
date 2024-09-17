/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 16:45:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.class.hpp"

Cat::Cat(void) {
	this->type = "Cat";
	this->brain = new Brain();
	std::cout << "Constructor Cat" << std::endl;
	return ;
}

Cat::Cat(Cat& in) {
	std::cout << "Copy constructor Cat" << std::endl;
	this->type = in.getType();
	this->brain = new Brain(*(in.getBrain()));
	return ;
}

Cat::~Cat(void) {
	std::cout << "Destructor Cat" << std::endl;
	delete this->brain;
	return ;
}

Brain* Cat::getBrain(void) {
	return this->brain;
}

std::string Cat::getType(void) {
	return this->type;
}

void Cat::setType(std::string type) {
	this->type = type;
}

void Cat::makeSound(void) const {
	std::cout << "Miaou" << std::endl;
}
