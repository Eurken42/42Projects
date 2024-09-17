/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:37:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/15 13:05:17 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_CLASS_HPP
# define CAT_CLASS_HPP

#include <iostream>
#include "Animal.class.hpp"

class Cat : public Animal {
	public :
		Cat(void);
		Cat(const Cat& in);
		virtual ~Cat(void);

		std::string getType() const;
		void setType(std::string);
		virtual void makeSound(void) const;

		Cat & operator = (const Cat& cat);
};

#endif
