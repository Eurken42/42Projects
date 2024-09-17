/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/15 13:06:35 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.class.hpp"

Dog::Dog(void) {
	this->type = "Dog";
	std::cout << "Constructor Dog" << std::endl;
	return ;
}

Dog::Dog(const Dog& in) {
	std::cout << "Copy constructor dog" << std::endl;
	*this = in;
	return ;
}

Dog::~Dog(void) {
	std::cout << "Destructor Dog" << std::endl;
	return ;
}

std::string Dog::getType(void) const {
	return this->type;
}

void Dog::setType(std::string type) {
	this->type = type;
}

void Dog::makeSound(void) const {
	std::cout << "Woaf" << std::endl;
}

Dog & Dog::operator = (const Dog& dog) {
	this->type = dog.getType();
	return *this;
}
