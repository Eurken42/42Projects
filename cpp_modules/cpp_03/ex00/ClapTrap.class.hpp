/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:11:28 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/10 15:29:58 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_CLASS_HPP
# define CLAPTRAP_CLASS_HPP

#include <iostream>

class ClapTrap {
	public :
		ClapTrap(const std::string name);
		ClapTrap(ClapTrap const &ClapTrap);
		~ClapTrap();

		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		std::string getName(void);
		unsigned int getHp(void);
		unsigned int getMana(void);
		unsigned int getDmg(void);
	
		void setHp(unsigned int amount);
		void setMana(unsigned int amount);
		void setDmg(unsigned int amount);
	private :
		std::string		name;
		unsigned int	hp;
		unsigned int	mana;
		unsigned int	dmg;
};

#endif
