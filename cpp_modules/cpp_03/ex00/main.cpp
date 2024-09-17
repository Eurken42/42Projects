/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:38:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/10 15:13:26 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.class.hpp"

int main() {
	ClapTrap steve("Steve");
	ClapTrap cindy("Cindy");

	std::cout << std::endl;
	steve.attack(cindy.getName());
	cindy.takeDamage(steve.getDmg());
	cindy.takeDamage(8);
	cindy.beRepaired(4);
	cindy.takeDamage(2);
	cindy.beRepaired(8);
	std::cout << std::endl;

	return 0;
}
