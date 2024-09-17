/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:37:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 16:45:54 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_CLASS_HPP
# define DOG_CLASS_HPP

#include <iostream>
#include "AAnimal.class.hpp"
#include "Brain.class.hpp"

class Dog : public AAnimal {
	public :
		Dog(void);
		Dog(Dog& in);
		~Dog(void);

		Brain* getBrain();
		std::string getType();
		void setType(std::string);
		virtual void makeSound(void) const;
	private : 
		Brain *brain;
};

#endif
