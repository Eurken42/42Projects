/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:31:02 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 14:05:52 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_CLASS_HPP
# define ANIMAL_CLASS_HPP

#include <iostream>

class Animal {
	public :
		Animal(void);
		Animal(const Animal& in);
		virtual ~Animal(void);

		std::string getType() const;
		void setType(std::string);
		virtual void makeSound(void) const;

		Animal & operator = (const Animal& an);
	protected : 
		std::string type;
};

std::ostream & operator << (std::ostream& os, Animal const &f);

#endif
