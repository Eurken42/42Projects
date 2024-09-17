/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:52 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 17:33:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.class.hpp"

int	main(int ac, char **av){
	Harl test;

	if (ac != 1)
		test.complain((std::string)av[1]);
	return 1;
}
