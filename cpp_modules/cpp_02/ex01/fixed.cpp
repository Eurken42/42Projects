/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:33:06 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/08 16:05:12 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.class.hpp"
#include <iostream>
/*
FRACT_BITS 8
FIXED_POINT_ONE (1 << FRACT_BITS)
MAKE_INT_FIXED(x) ((x) << FRACT_BITS)
MAKE_FLOAT_FIXED(x) (ROUNDF((x) * FIXED_POINT_ONE))
MAKE_FIXED_INT(x) ((x) >> FRACT_BITS)
MAKE_FIXED_FLOAT(x) (((float)(x)) / FIXED_POINT_ONE)

ROUNDF Arrondit une valeur à virgule flottante à la valeur entière la plus proche.
*/
Fixed::Fixed (void) {
	this->nb = 0;
	std::cout << "Default constructor called" << std::endl; 
	return ;
}

Fixed::Fixed (const int nb) {
	this->setRawBits(nb << this->bits);
	std::cout << "Int constructor called" << std::endl;
	return ;
}

Fixed::Fixed (const float nb) {
	this->setRawBits(roundf(nb * (1 << this->bits)));
	std::cout << "Float constructor called" << std::endl;
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
	return (this->nb);
}

void Fixed::setRawBits (const int nb) {
	this->nb = nb;
}

float Fixed::toFloat(void) const {
	return ((float)this->getRawBits() / (1 << this->bits));
}

int Fixed::toInt(void) const {
	return (this->getRawBits() >> this->bits);
}

Fixed & Fixed::operator = (Fixed const &f) {
	setRawBits(f.getRawBits());
	return (*this);
}

std::ostream & operator << (std::ostream& os, Fixed const &f) {
	os << f.toFloat();
	return (os);
}
