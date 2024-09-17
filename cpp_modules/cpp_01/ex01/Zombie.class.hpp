/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:00:51 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 16:17:29 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <cstring>

class Zombie {
	public:
		Zombie(void);
		~Zombie(void);

		std::string getName(void);
		void setName(std::string name);
		void annonce(void);
	private:
		std::string	name;
};

Zombie *zombieHorde(int N, std::string name);

#endif
