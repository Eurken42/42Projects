/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:45:29 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/06 13:40:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_CLASS_HPP
# define ARRAY_CLASS_HPP

#include <iostream>

template<typename T>
class Array {
	public :
		Array<T>(void) {
			this->_size = 0;
			this->tab = new T[this->_size];
		}

		Array<T>(unsigned int n) {
			this->_size = n;
			this->tab = new T[n];
		}

		Array<T>(Array<T> & cpy) {
			*this = cpy;
			return ;
		}

		~Array<T>(void) {
			return ;
		}

		unsigned int size(void) {
			return this->_size;
		}

		Array<T> & operator = (Array<T> & cpy) {
			unsigned int i = 0;
			if (&cpy == this)
				return *this;
			this->_size = cpy._size;
			this->tab = new T [this->_size];
			while (i < this->_size) {
				this->tab[i] = cpy[i];
				i++;
			}
			return *this;	
		}
		
		T & operator [] (int i) {
			if (i > (int)this->size() - 1 || i < 0)
				throw std::exception();
			return this->tab[i];
		}

	private :
		T *tab;
		unsigned int _size;
};

template<typename T>
std::ostream & operator << (std::ostream& os, Array<T> &f) {
	os << "LEN -> " << f.size() << std::endl;
	unsigned int i = 0;
	while (i < f.size()) {
		os << "[" << i << "] " << f[i] << std::endl;
		i++;
	}
	return os;
}
#endif
