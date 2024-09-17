/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scavtrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:16:10 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/10 16:56:16 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.class.hpp"

ScavTrap::ScavTrap (const std::string name): ClapTrap(name) {
	this->name = name;
	this->hp = 100;
	this->mana = 50;
	this->dmg = 20;
	std::cout << "Constructor called of ScavTrap " << name << std::endl;
	return ;
}

ScavTrap::~ScavTrap (void) {
	std::cout << "Destructor called of ScavTrap " << getName() << std::endl;
	return ;
}

void	ScavTrap::attack(const std::string& target) {
	if (getMana() >= 1 && getHp() >= 1) {
		std::cout << "ScavTrap " << getName() << " attack " << target;
		std::cout << ", causing " << getDmg() << " points of damage !" << std::endl;
		setMana(getMana() - 1);
	}
	else
		std::cout << "Can't Attack cause of no Mana or HP" << std::endl;
}

void ScavTrap::guardGate(void) {
	std::cout << "ScavTrap has entered Gate keeper mode !" << std::endl;
}
