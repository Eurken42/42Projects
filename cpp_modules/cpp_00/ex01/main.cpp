/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:16:00 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/04 13:43:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include "Phonebook.class.hpp"
#include "Contact.class.hpp"

int	main(void)
{
	Phonebook	phonebook;
	std::string	input;

	std::cout << "PhoneBook" << std::endl << "---------" << std::endl;
	while (42)
	{
		std::cout << std::endl << "What do you want to do (ADD, SEARCH, EXIT) ?" << std::endl;
		std::cin >> input;
		if (input == "ADD")
			phonebook.add_contact(&phonebook);
		else if (input == "SEARCH")
			phonebook.search_contact(phonebook);
		else if (input == "EXIT")
			break;
		else
		std::cout << "Invalid request !" << std::endl;
	}
	return (0);
}
