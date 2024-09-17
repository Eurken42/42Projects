/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:45:29 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/02 16:00:04 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_CLASS_HPP
# define MAIN_CLASS_HPP

template<typename T>
T const & max(T const& x, T const& y) {
	return (x < y ? y : x);
}

template<typename T>
T const & min(T const& x, T const& y) {
	return (x > y ? y : x);
}

template<typename T>
void swap(T& x, T& y) {
	T z = x;
	x = y;
	y = z;
	return ;
}
#endif
