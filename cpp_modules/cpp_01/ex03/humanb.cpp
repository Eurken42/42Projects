/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   humanb.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:05:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 17:26:20 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.class.hpp"
#include "Weapon.class.hpp"

HumanB::HumanB (std::string name): name(name){
	this->wp = NULL;
	return;
}

HumanB::~HumanB (void) {
 	return;
}

void HumanB::attack(void){
	std::cout << HumanB::getName() << " attacks with their " << (*(this->wp)).getType() << std::endl;
}

std::string HumanB::getName (void){
 	return (this->name);
}

void	HumanB::setWeapon(Weapon &wp){
	this->wp = &wp;
}
