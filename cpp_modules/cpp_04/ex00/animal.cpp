/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:33:34 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 12:01:16 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.class.hpp"

Animal::Animal(void) {
	std::cout << "Constructor Animal" << std::endl;
	return ;
}

Animal::Animal(const Animal& in) {
	std::cout << "Copy constructor Animal" << std::endl;
	*this = in;
	return ;
}

Animal::~Animal(void) {
	std::cout << "Destructor Animal" << std::endl;
	return ;
}

std::string Animal::getType(void) const {
	return this->type;
}

void Animal::setType(std::string type) {
	this->type = type;
}

void Animal::makeSound(void) const {
	std::cout << "No sound" << std::endl;
}

Animal & Animal::operator = (const Animal& an) {
	this->type = an.getType();
	return *this;
}

std::ostream & operator << (std::ostream& os, Animal const &f) {
	os << f.getType();
	return (os);
}
