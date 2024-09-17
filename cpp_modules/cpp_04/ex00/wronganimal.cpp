/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:33:34 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 14:00:48 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.class.hpp"

WrongAnimal::WrongAnimal(void) {
	std::cout << "Constructor WrongAnimal" << std::endl;
	return ;
}

WrongAnimal::WrongAnimal(const WrongAnimal& in) {
	std::cout << "Copy constructor WrongAnimal" << std::endl;
	*this = in;
	return ;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "Destructor WrongAnimal" << std::endl;
	return ;
}

std::string WrongAnimal::getType(void) const {
	return this->type;
}

void WrongAnimal::setType(std::string type) {
	this->type = type;
}

void WrongAnimal::makeSound(void) const {
	std::cout << "No sound" << std::endl;
}

WrongAnimal & WrongAnimal::operator = (const WrongAnimal& an) {
	this->type = an.getType();
	return *this;
}

std::ostream & operator << (std::ostream& os, WrongAnimal const &f) {
	os << f.getType();
	return (os);
}
