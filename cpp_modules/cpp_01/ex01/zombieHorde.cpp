/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:01:57 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 16:17:27 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.class.hpp"

Zombie *zombieHorde( int N, std::string name ){
	Zombie *hordeZM = new Zombie[N];
	while (--N >= 0)
		hordeZM[N].setName(name);
	return (hordeZM);
}
