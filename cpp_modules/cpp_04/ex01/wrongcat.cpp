/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 14:02:37 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.class.hpp"

WrongCat::WrongCat(void) {
	this->type = "WrongCat";
	std::cout << "Constructor WrongCat" << std::endl;
	return ;
}

WrongCat::WrongCat(const WrongCat& in) {
	std::cout << "Copy constructor WrongCat" << std::endl;
	*this = in;
	return ;
}

WrongCat::~WrongCat(void) {
	std::cout << "Destructor WrongCat" << std::endl;
	return ;
}

std::string WrongCat::getType(void) {
	return this->type;
}

void WrongCat::setType(std::string type) {
	this->type = type;
}

void WrongCat::makeSound(void) const {
	std::cout << "Miaou" << std::endl;
}
