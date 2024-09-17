/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragtap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:53:42 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/10 17:05:18 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.class.hpp"

FragTrap::FragTrap (const std::string name): ClapTrap(name) {
	this->name = name;
	this->hp = 100;
	this->mana = 100;
	this->dmg = 30;
	std::cout << "Constructor called of FragTap " << name << std::endl;
	return ;
}

FragTrap::~FragTrap (void) {
	std::cout << "Destructor called of FragTap " << getName() << std::endl;
	return ;
}

void	FragTrap::attack(const std::string& target) {
	if (getMana() >= 1 && getHp() >= 1) {
		std::cout << "FragTrap " << getName() << " attack " << target;
		std::cout << ", causing " << getDmg() << " points of damage !" << std::endl;
		setMana(getMana() - 1);
	}
	else
		std::cout << "Can't Attack cause of no Mana or HP" << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap uhm High Five !" << std::endl;
}
