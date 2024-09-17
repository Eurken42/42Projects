/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:00:51 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 17:18:56 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_CLASS_HPP
# define HUMANA_CLASS_HPP

#include "Weapon.class.hpp"

class HumanA {
	public:
		HumanA(std::string name, Weapon& wp);
		~HumanA(void);

		void attack(void);
		std::string getName(void);
	private:
		std::string	name;
		Weapon &wp;
};

#endif
