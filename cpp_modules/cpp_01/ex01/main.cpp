/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:13:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 16:17:32 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.class.hpp"

int	main(void)
{
	int		nb = 5;
	Zombie	*Horde;

	Horde = zombieHorde(nb, "Daniel");
	while (--nb >= 0)
		Horde[nb].annonce();
	delete [] Horde;
	return (0);
}
