/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:37:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 16:45:22 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_CLASS_HPP
# define CAT_CLASS_HPP

#include <iostream>
#include "AAnimal.class.hpp"
#include "Brain.class.hpp"

class Cat : public AAnimal {
	public :
		Cat(void);
		Cat(Cat& in);
		virtual ~Cat(void);

		Brain* getBrain();
		std::string getType();
		void setType(std::string);
		virtual void makeSound(void) const;
	private :
		Brain *brain;
};

#endif
