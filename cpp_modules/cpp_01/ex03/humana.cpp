/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   humana.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:05:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 17:26:17 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.class.hpp"
#include "Weapon.class.hpp"

HumanA::HumanA (std::string name, Weapon& wp): name(name), wp(wp){
	return;
}

HumanA::~HumanA (void) {
 	return;
}

void HumanA::attack(void){
	std::cout << HumanA::getName() << " attacks with their " << this->wp.getType() << std::endl;
}

std::string HumanA::getName (void){
 	return (this->name);
}
