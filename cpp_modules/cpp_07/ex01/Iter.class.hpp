/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iter.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:45:29 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/05 13:45:27 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_CLASS_HPP
# define ITER_CLASS_HPP

template<typename T>
void iter(T* x, int y, void(*funct)(T const&)) {
	int i = -1;
	if (y >= 1)
		while (++i < y)
			funct(x[i]);
	return ;
}

template<typename T>
void ft_display(T &value) {
	std::cout << "'" << value << "'";
}
#endif
