/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:28:16 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/09 16:03:48 by scorreia         ###   ########.fr       */
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

		static Fixed & min(Fixed& f1, Fixed& f2);
		static Fixed const & min(Fixed const& f1, Fixed const& f2);
		
		static Fixed & max(Fixed& f1, Fixed& f2);
		static Fixed const & max(Fixed const& f1, Fixed const& f2);


		bool operator > (Fixed const &f) const;
		bool operator < (Fixed const &f) const;
		bool operator >= (Fixed const &f) const;
		bool operator <= (Fixed const &f) const;
		bool operator == (Fixed const &f) const;
		bool operator != (Fixed const &f) const;

		Fixed & operator ++ (void);
		Fixed & operator -- (void);
		Fixed operator ++ (int);
		Fixed operator -- (int);

		Fixed & operator = (Fixed f);
		Fixed operator + (Fixed const &f) const;
		Fixed operator - (Fixed const &f) const;
		Fixed operator * (Fixed const &f) const;
		Fixed operator / (Fixed const &f) const;

		friend std::ostream & operator << (std::ostream& os, Fixed const &f);
		Fixed & operator = (Fixed const &f);
	private:
		int nb;
		static const int bits = 8;
};

#endif
