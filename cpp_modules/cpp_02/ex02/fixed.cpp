/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:33:06 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/09 16:03:46 by scorreia         ###   ########.fr       */
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
Fixed::Fixed (void): nb(0) {
	return ;
}

Fixed::Fixed (const int nb) {
	this->setRawBits(nb << this->bits);
	return ;
}

Fixed::Fixed (const float nb) {
	this->setRawBits(roundf(nb * (1 << this->bits)));
	return ;
}

Fixed::Fixed (Fixed const &Fixed) {
	this->nb = Fixed.getRawBits();
}

Fixed::~Fixed (void) {
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

Fixed & Fixed::operator = (Fixed f) {
	std::swap(this->nb, f.nb);
	return (*this);
}

//Min max

Fixed & Fixed::min(Fixed& f1, Fixed& f2) {
	if (f1 < f2)
		return f1;
	return f2;
}

Fixed const & Fixed::min(Fixed const& f1, Fixed const& f2) {
	if (f1 < f2)
		return f1;
	return f2;
}

Fixed & Fixed::max(Fixed& f1, Fixed& f2) {
	if (f1 > f2)
		return f1;
	return f2;
}

Fixed const & Fixed::max(Fixed const& f1, Fixed const & f2) {
	if (f1 > f2)
		return f1;
	return f2;
}

//end

//Les 6 opérateur de comparaison : >, <, >=, <=, == et !=

bool Fixed::operator > (Fixed const &f) const {
	if (this->getRawBits() > f.getRawBits())
		return true;
	return false;
}

bool Fixed::operator < (Fixed const &f) const {
	if (this->getRawBits() < f.getRawBits())
		return true;
	return false;
}

bool Fixed::operator >= (Fixed const &f) const {
	if (this->getRawBits() >= f.getRawBits())
		return true;
	return false;
}

bool Fixed::operator <= (Fixed const &f) const {
	if (this->getRawBits() <= f.getRawBits())
		return true;
	return false;
}

bool Fixed::operator == (Fixed const &f) const {
	if (this->getRawBits() == f.getRawBits())
		return true;
	return false;
}

bool Fixed::operator != (Fixed const &f) const {
	if (this->getRawBits() != f.getRawBits())
		return true;
	return false;
}

//end


//Les 4 opérateurs de arithmétiques : +, -, *, et /

Fixed Fixed::operator + (Fixed const &f) const {
	Fixed tmp(this->toFloat() + f.toFloat());
	return tmp;
}

Fixed Fixed::operator - (Fixed const &f) const {
	Fixed tmp(this->toFloat() - f.toFloat());
	return tmp;
}

Fixed Fixed::operator * (Fixed const &f) const {
	Fixed tmp(this->toFloat() * f.toFloat());
	return tmp;
}

Fixed Fixed::operator / (Fixed const &f) const {
	Fixed tmp(this->toFloat() / f.toFloat());
	return tmp;
}

//end

//Les 4 opérateurs d’incrémentation et de décrémentation

Fixed & Fixed::operator ++ (void) { //++nb
	this->nb += 1;
	return (*this);
}

Fixed & Fixed::operator -- (void) { //--nb
	this->nb -=1;
	return (*this);
}

Fixed Fixed::operator ++ (int) { //nb++
	Fixed temp = *this;
	++*this;
	return temp;
}

Fixed Fixed::operator -- (int) { //nb--
	Fixed temp = *this;
	--*this;
	return temp;
}

//end

std::ostream & operator << (std::ostream& os, Fixed const &f) {
	os << f.toFloat();
	return (os);
}
