/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:41:51 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/13 16:28:59 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_CLASS_HPP
# define MUTANTSTACK_CLASS_HPP

#include <iostream>
#include <stack>
#include <algorithm>
#include <iterator>

template<typename T>
class MutantStack: public std::stack<T> {
	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	
		MutantStack<T> (void) { return ; }
		~MutantStack<T> (void) { return ; }
		
		MutantStack<T>(MutantStack<T> &cpy) { 
			*this = cpy;
			return ;
		}
		
		MutantStack<T> & operator = (MutantStack<T> & cpy) {
			std::stack<T>::c = cpy.c;
			return *this;
		}

		iterator begin() {
			return std::stack<T>::c.begin();
		}
		iterator end() {
			return std::stack<T>::c.end();
		}

		iterator begin() const {
			return std::stack<T>::c.begin();
		}
		iterator end() const {
			return std::stack<T>::c.end();
		}
};

#endif
