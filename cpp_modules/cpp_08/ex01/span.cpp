/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:13:45 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/07 14:39:30 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.class.hpp"
#include <iostream>


Span::Span(unsigned int nb): _n(nb), _nb(nb) {
	return ;
}

Span::~Span(void) {
	return ;
}

void Span::addNumber(int nb) {
	if (_n > 0) {
		this->_numbers.push_back(nb);
		this->_n -= 1;
	} else
		throw std::exception();		
}

int Span::shortestSpan(void) const {
	std::list<int>::const_iterator it = this->_numbers.begin();
	std::list<int>::const_iterator ite = this->_numbers.end();
	int distance = -1;
	int size = this->_nb - this->_n;
	int tab[size];
	int i = -1;
	int j;
	int tmp;

	while (it != ite) {
		tab[++i] = *it;
		it++;
	}
	i = -1;
	while (++i < size) {
		j = -1;
		while (++j < size) {
			if (j != i) {
				tmp = tab[i] - tab[j];
				if (tmp < 0)
					tmp *= -1;
				if (tmp < distance || distance == -1)
					distance = tmp;
				if (distance == 0)
					return distance;
			}
		}
	}
	if (distance == -1)
		throw std::exception();
	return distance;
}

int Span::longestSpan(void) const {
	std::list<int>::const_iterator it = this->_numbers.begin();
	std::list<int>::const_iterator ite = this->_numbers.end();
	int distance = -1;
	int size = this->_nb - this->_n;
	int tab[size];
	int i = -1;
	int j;
	int tmp;

	while (it != ite) {
		tab[++i] = *it;
		it++;
	}
	i = -1;
	while (++i < size) {
		j = -1;
		while (++j < size) {
			if (j != i) {
				tmp = tab[i] - tab[j];
				if (tmp < 0)
					tmp *= -1;
				if (tmp > distance || distance == -1)
					distance = tmp;
			}
		}
	}
	if (distance == -1)
		throw std::exception();
	return distance;
}

std::ostream & operator << (std::ostream& os, const Span& in) {
	os << "Shortest -> " << in.shortestSpan() << std::endl;
	os << "Longest -> " << in.longestSpan();
	return (os);
}
