/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:43:24 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/06 13:47:08 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Iter.class.hpp"

int main(void) {
	std::string ok[2] = { "42 ", "Lausanne" };
	int ok2[2] = { 129, 900 };
	
	::iter(ok, 2, &ft_display);
	std::cout << std::endl;
	::iter(ok2, 2, &ft_display);
	return 0;
}
