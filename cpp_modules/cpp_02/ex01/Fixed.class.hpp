/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:28:16 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/08 16:05:22 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

#include <iostream>

class Fixed {
	public:
		Fixed(void);
		Fixed(const int nb);
		Fixed(const float nb);
		Fixed(Fixed const &Fixed);
		~Fixed(void);

		int getRawBits(void) const;
		void setRawBits(int const nb);

		float toFloat(void) const;
		int toInt(void) const;

		Fixed & operator = (Fixed const &f);
		friend std::ostream & operator << (std::ostream& os, Fixed const &f);
	private:
		int nb;
		static const int bits = 8;
};

#endif
