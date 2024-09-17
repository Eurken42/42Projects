/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:16:23 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/13 16:37:02 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.class.hpp"
#include <iostream>
#include <iterator>
#include <stack>
#include <algorithm>

int main(void) {
	MutantStack<int> mstack;
	
	mstack.push(5);
	mstack.push(17);
	
	std::cout << "Top element -> " << mstack.top() << std::endl << "Remove top element" << std::endl;
	mstack.pop();
	std::cout << "Size -> " << mstack.size() << std::endl << std::endl << "DATA" << std::endl;
	
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	
	
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;

	MutantStack<int> cpy = mstack;
	it = cpy.begin();
	ite = cpy.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;

	MutantStack<int> cpy2(mstack);
	it = cpy2.begin();
	ite = cpy2.end();
	++it;
	--it;

	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}

	std::stack<int> s(mstack);
	return 0;
}
