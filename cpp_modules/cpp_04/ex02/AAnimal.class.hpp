/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:31:02 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/14 16:00:30 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_CLASS_HPP
# define AANIMAL_CLASS_HPP

#include <iostream>

class AAnimal {
	public :
		AAnimal(void);
		virtual ~AAnimal(void) = 0;

		std::string getType() const;

		AAnimal & operator = (const AAnimal& an);
	protected : 
		std::string type;
};

std::ostream & operator << (std::ostream& os, AAnimal const &f);

#endif
