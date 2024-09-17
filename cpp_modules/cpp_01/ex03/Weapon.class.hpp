/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:00:51 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 17:19:56 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_CLASS_HPP
# define WEAPON_CLASS_HPP

#include <iostream>
#include <cstring>

class Weapon {
	public:
		Weapon(std::string type);
		~Weapon(void);

		std::string const & getType(void);
		void setType(const std::string& type);
	private:
		std::string	type;
};

#endif
