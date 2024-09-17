/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:40:56 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 15:10:42 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.class.hpp"
#include "Cat.class.hpp"
#include "WrongCat.class.hpp"
#include "Brain.class.hpp"

int main()
{
	int	i = -1;
	int MAX = 10;
	Animal *animals[MAX];
	
	while (++i < MAX) {
		(i < MAX) ? animals[i] = new Dog() : animals[i] = new Cat();
		std::cout << i << " " << animals[i]->getType() << std::endl;
	}
	i  = -1;
	while (++i < MAX) {
		std::cout << i << std::endl;
		delete animals[i];
	}
	return 0;
}
