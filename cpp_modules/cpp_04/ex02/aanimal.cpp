/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aanimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:33:34 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 16:00:38 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.class.hpp"

AAnimal::AAnimal(void) {
	std::cout << "Constructor AAnimal" << std::endl;
	return ;
}

AAnimal::~AAnimal(void) {
	std::cout << "Destructor AAnimal" << std::endl;
	return ;
}

std::string AAnimal::getType(void) const {
	return this->type;
}

AAnimal & AAnimal::operator = (const AAnimal& an) {
	this->type = an.getType();
	return *this;
}

std::ostream & operator << (std::ostream& os, AAnimal const &f) {
	os << f.getType();
	return (os);
}
