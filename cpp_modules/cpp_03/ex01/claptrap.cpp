/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   claptrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:15:02 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/10 16:59:22 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.class.hpp"

ClapTrap::ClapTrap (std::string name): name(name), hp(10), mana(10), dmg(1){
	std::cout << "Constructor called of " << name << std::endl;
	return ;
}

ClapTrap::ClapTrap (ClapTrap const& ClapTrap) {
	*this = ClapTrap;
	std::cout << "Copy assignment operator called" << std::endl;
}

ClapTrap::~ClapTrap (void) {
	std::cout << "Destructor called of " << getName() << std::endl;
	return ;
}

void	ClapTrap::attack(const std::string& target) {
	if (getMana() >= 1 && getHp() >= 1) {
		std::cout << "ClapTrap " << getName() << " attack " << target;
		std::cout << ", causing " << getDmg() << " points of damage !" << std::endl;
		setMana(getMana() - 1);
	}
	else
		std::cout << "Can't Attack cause of no Mana or HP" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (getHp() != 0) {
		if (getHp() < amount)
			setHp(0);
		else
			setHp(getHp() - amount);
		std::cout << "ClapTrap " << getName() << " Take " << amount;
		std::cout << " damage, new HP " << getHp() << " HP !" << std::endl;
	}
	else
		std::cout << "Already dead..." << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (getMana() >= 1 && getHp() >= 1) {
		setHp(getHp() + amount);
		setMana(getMana() - 1);
		std::cout << "ClapTrap " << getName() << " heal " << amount << " HP";
		std::cout << ", new hp " << getHp() << " HP !" << std::endl;
	}
	else
		std::cout << "Can't Repair cause of no Mana or HP" << std::endl;
}

std::string ClapTrap::getName (void) {
	return this->name;
}

unsigned int ClapTrap::getHp (void) {
	return this->hp;
}

unsigned int ClapTrap::getMana (void) {
	return this->mana;
}

unsigned int ClapTrap::getDmg (void) {
	return this->dmg;
}

void ClapTrap::setHp (unsigned int amount) {
	this->hp = amount;
}

void ClapTrap::setMana (unsigned int amount) {
	this->mana = amount;
}

void ClapTrap::setDmg (unsigned int amount) {
	this->dmg = amount;
}
