/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:11:39 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/07 14:39:47 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_CLASS_HPP
# define SPAN_CLASS_HPP

#include <list>

class Span {
	public : 
		Span(unsigned int nb);
		~Span(void);

		void addNumber(int nb);
		int shortestSpan(void) const;
		int longestSpan(void) const;
	private :
		unsigned int _n;
		unsigned int _nb;
		std::list<int> _numbers;
};

std::ostream & operator << (std::ostream& os, const Span& in);

#endif
