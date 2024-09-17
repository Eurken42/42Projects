/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:05:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 16:17:25 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.class.hpp"

Zombie::Zombie (void): name("") {
	return;
}

Zombie::~Zombie (void) {
	std::cout << Zombie::getName() << " Dying... That's sad :(" << std::endl;
 	return;
}

std::string Zombie::getName (void){
 	return (this->name);
}

void Zombie::setName(std::string name){
	this->name = name;
}

void	Zombie::annonce(void){
	std::cout << Zombie::getName() << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
