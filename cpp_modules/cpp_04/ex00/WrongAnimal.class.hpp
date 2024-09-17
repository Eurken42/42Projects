/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:31:02 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 14:06:21 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_CLASS_HPP
# define WRONGANIMAL_CLASS_HPP

#include <iostream>

class WrongAnimal {
	public :
		WrongAnimal(void);
		WrongAnimal(const WrongAnimal& in);
		virtual ~WrongAnimal(void);

		std::string getType() const;
		void setType(std::string);
		virtual void makeSound(void) const;

		WrongAnimal & operator = (const WrongAnimal& an);
	protected : 
		std::string type;
};

std::ostream & operator << (std::ostream& os, WrongAnimal const &f);

#endif
