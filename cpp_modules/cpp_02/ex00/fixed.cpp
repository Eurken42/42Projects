/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:33:06 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/08 12:52:13 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.class.hpp"
#include "iostream"

Fixed::Fixed (void) {
	this->nb = 0;
	std::cout << "Default constructor called" << std::endl; 
	return ;
}

Fixed::Fixed (Fixed const &Fixed) {
	*this = Fixed;
	std::cout << "Copy assignment operator called" << std::endl; 
}

Fixed::~Fixed (void) {
	std::cout << "Destructor called" << std::endl; 
	return ;
}

int	Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl; 
	return (this->nb);
}

void Fixed::setRawBits (const int nb) {
	this->nb = nb;
}

Fixed & Fixed::operator = (Fixed const &f) {
	setRawBits(f.getRawBits());
	return (*this);
}
