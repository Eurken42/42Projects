/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:13:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 15:50:55 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.class.hpp"

int	main(void)
{
	Zombie steve("Steve");
	steve.annonce();
	Zombie *alfred = new Zombie("Alfred");
	alfred->annonce();
	delete alfred;
	randomChump("Cindy");
	return (0);
}
