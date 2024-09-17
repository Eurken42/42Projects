/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:00:51 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 13:54:57 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <cstring>

class Zombie {
	public:
		Zombie(std::string name);
		~Zombie(void);

		std::string getName(void);
		void setName(std::string name);
		void annonce(void);
	private:
		std::string	name;
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif
