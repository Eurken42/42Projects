/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 16:46:48 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.class.hpp"

Dog::Dog(void) {
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "Constructor Dog" << std::endl;
	return ;
}

Dog::Dog(Dog& in) {
	std::cout << "Copy constructor dog" << std::endl;
	this->type = in.getType();
	this->brain = new Brain(*(in.getBrain()));
	return ;
}

Dog::~Dog(void) {
	std::cout << "Destructor Dog" << std::endl;
	delete this->brain;
	return ;
}

Brain* Dog::getBrain(void) {
	return this->brain;
}

std::string Dog::getType(void) {
	return this->type;
}

void Dog::setType(std::string type) {
	this->type = type;
}

void Dog::makeSound(void) const {
	std::cout << "Woaf" << std::endl;
}
