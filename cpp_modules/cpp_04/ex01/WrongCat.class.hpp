/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:37:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 14:06:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_CLASS_HPP
# define WRONGCAT_CLASS_HPP

#include <iostream>
#include "WrongAnimal.class.hpp"

class WrongCat : public WrongAnimal {
	public :
		WrongCat(void);
		WrongCat(const WrongCat& in);
		virtual ~WrongCat(void);

		std::string getType();
		void setType(std::string);
		virtual void makeSound(void) const;
};

#endif
