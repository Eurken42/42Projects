/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:43:24 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/06 13:44:49 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Whatever.class.hpp"

int main(void) {
	int a = 20;
	int b = 30;
	std::string a2 = "31";
	std::string b2 = "30";

	std::cout << "a " << a << std::endl;
	std::cout << "b " << b << std::endl;
	std::cout << "Max : " << ::max(a, b) << std::endl;
	std::cout << "Min : " << ::min(a, b) << std::endl;

	std::cout << "a2 " << a2 << std::endl;
	std::cout << "b2 " << b2 << std::endl;
	std::cout << "Max : " << ::max(a2, b2) << std::endl;
	std::cout << "Min : " << ::min(a2, b2) << std::endl;

	std::cout << std::endl;

	std::cout << "a " << a << std::endl;
	std::cout << "b " << b << std::endl;
	::swap(a, b);
	std::cout << "Swap " << std::endl << a << std::endl;
	std::cout << b << std::endl;
	
	std::cout << std::endl;

	std::cout << "a2 " << a2 << std::endl;
	std::cout << "b2 " << b2 << std::endl;
	::swap(a2, b2);
	std::cout << "Swap " << std::endl << a2 << std::endl;
	std::cout << b2 << std::endl;
	return 0;
}
