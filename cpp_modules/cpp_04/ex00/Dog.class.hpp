/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:37:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/15 13:06:22 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_CLASS_HPP
# define DOG_CLASS_HPP

#include <iostream>
#include "Animal.class.hpp"

class Dog : public Animal {
	public :
		Dog(void);
		Dog(const Dog& in);
		virtual ~Dog(void);

		std::string getType() const;
		void setType(std::string);
		virtual void makeSound(void) const;
		Dog & operator = (const Dog& dog);
};

#endif
