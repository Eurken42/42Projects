/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:26:45 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/04 14:43:51 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Contact.class.hpp"
#include "Phonebook.class.hpp"
#include <string>
#include <iomanip>

Phonebook::Phonebook (void) {
	count = 0;
	return;
 }

 Phonebook::~Phonebook (void) {
 	return;
 }

Contact	Phonebook::getContact(int i)
{
	return (this->contact[i]);
}

void	Phonebook::setContact(int i, int i2)
{
	this->contact[i] = this->contact[i2];
}

std::string trim_string(std::string info)
{
	if (info.size() > 9)
		return (info.substr(0, 9).append("."));
	return (info);
}

void set_fill(std::string str, std::string pipe)
{
	std::cout << std::setfill(' ') << std::setw(10) << trim_string(str) << pipe; 
}

void	display_index_summary(Contact ct, int i)
{
	std::cout << std::setfill(' ') << std::setw(10) << i + 1 << " | ";
	set_fill(ct.getFirstName(), " | ");
	set_fill(ct.getLastName(), " | ");
	set_fill(ct.getNickName(), " |");
	std::cout << std::endl;
}

void	display_index_info(Contact ct)
{
	std::cout << "First name: " << ct.getFirstName() << std::endl;
	std::cout << "Last name: " << ct.getLastName() << std::endl;
	std::cout << "Nickname: " << ct.getNickName() << std::endl;
	std::cout << "Phone number: " << ct.getPhone() << std::endl;
	std::cout << "Darkest secret: " << ct.getSecret() << std::endl;
}

void	Phonebook::search_contact(Phonebook pb)
{
	int	i = -1;
	Contact ct;
	int num;

	std::cout << std::endl << "LIST USER" << std::endl << "---------" << std::endl;
	if (pb.count == 0)
		std::cout << "EMPTY LIST !" << std::endl;
	else {
		while (++i < pb.count)
		{
			ct = getContact(i);
			display_index_summary(ct, i);
		}
		std::cout << std::endl;
		std::cout << "Choose an index to display : ";
		while (!(std::cin >> num) || num > pb.count || num < 1)
		{
			std::cout << "Error between 1 to " << pb.count << " : ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		std::cout << std::endl;
		ct = getContact(num - 1);
		display_index_info(ct);
	}
}

void	Phonebook::add_contact(Phonebook *pb)
{
	std::string	fn;
	std::string	ln;
	std::string	n;
	std::string	pn;
	std::string	s;
	int			id = pb->count;

	std::cout << "First name : ";
	std::cin >> fn;
	std::cout << "Last name : ";
	std::cin >> ln;
	std::cout << "Nickname : ";
	std::cin >> n;
	std::cout << "Phone number : ";
	std::cin >> pn;
	std::cout << "Secret : ";
	std::cin >> s;
	if (id == 8)
	{
		int j = -1;
		id = 7;
		while (++j < 7)
			pb->setContact(j, j + 1);
	}
	pb->contact[id].setFirstName(fn);
	pb->contact[id].setLastName(ln);
	pb->contact[id].setPhone(pn);
	pb->contact[id].setNickName(n);
	pb->contact[id].setSecret(s);
	if (pb->count != 8)
		pb->count++;
	return ;
}
