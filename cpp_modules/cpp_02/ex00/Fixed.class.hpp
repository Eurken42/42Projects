/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:28:16 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/08 12:49:15 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

class Fixed {
	public:
		Fixed(void);
		Fixed(Fixed const &Fixed);
		~Fixed(void);

		int getRawBits(void) const;
		void setRawBits(int const nb);

		Fixed & operator = (Fixed const &f);
	private:
		int nb;
		static const int bits = 8;
};

#endif
