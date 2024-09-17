/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:05:25 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 17:21:35 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.class.hpp"

Weapon::Weapon (std::string type): type(type){
	return;
}

Weapon::~Weapon (void) {
 	return;
}

std::string const & Weapon::getType (void){
 	return (this->type);
}

void	Weapon::setType(const std::string& type){
	this->type = type;
}
