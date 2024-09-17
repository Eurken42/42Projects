/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:27:28 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/06 16:12:07 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Easyfind.class.hpp"
#include <iostream>
#include <list>

int main(void) {
	std::list<int> lst1;

	lst1.push_back(4);
	lst1.push_back(6);
	lst1.push_back(-999);
	lst1.push_back(-6);
	lst1.push_back(1);
	lst1.push_back(-999);
	lst1.push_back(99);
	lst1.push_back(42);

	std::cout << "10 on list -> ";
	::easyfind(lst1, 10);
	std::cout << "42 on list -> ";
	::easyfind(lst1, 42);
	std::cout << "-999 on list -> ";
	::easyfind(lst1, -999);
	std::cout << "999 on list -> ";
	::easyfind(lst1, 999);
	return 0;
}
