/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:38:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/10 17:11:08 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.class.hpp"
#include "FragTrap.class.hpp"

int main() {
	ClapTrap steve("Steve");
	ScavTrap cindy("Cindy");
	FragTrap kelly("Kelly");

	std::cout << std::endl;
	cindy.attack(steve.getName());
	steve.takeDamage(steve.getDmg());
	steve.takeDamage(8);
	steve.beRepaired(4);
	steve.takeDamage(2);
	steve.beRepaired(8);
	std::cout << std::endl;

	steve.attack(cindy.getName());
	cindy.takeDamage(steve.getDmg());
	cindy.takeDamage(8);
	cindy.beRepaired(4);
	cindy.takeDamage(2);
	cindy.beRepaired(8);
	cindy.guardGate();
	std::cout << std::endl;

	kelly.attack(kelly.getName());
	kelly.takeDamage(steve.getDmg());
	kelly.takeDamage(8);
	kelly.beRepaired(4);
	kelly.takeDamage(2);
	kelly.beRepaired(8);
	kelly.highFivesGuys();
	std::cout << std::endl;
	return 0;
}
