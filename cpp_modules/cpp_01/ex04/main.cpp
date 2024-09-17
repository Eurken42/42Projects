/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:45:14 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/07 15:46:29 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <fstream>

std::string ft_replace(std::string buf, std::string s1, std::string s2)
{
	std::size_t start_pos = buf.find(s1);
	if (start_pos != std::string::npos)
	{
		buf.erase(start_pos, s1.length());
		buf.insert(start_pos, s2);
	}
	return (buf);
}

int	main(int ac, char **av)
{
	if (ac != 4) {
		std::cout << "Bad arguments : ./sed FILENAME STRING_1 STRING_2" << std::endl;
		return -1;
	}
	std::string buf;
	std::ifstream in;
	std::ofstream out;
	std::string old_file = (std::string)av[1];
	std::string new_file = old_file + ".replace";
	
	in.open(old_file);
	out.open(new_file);
	if (in.is_open() && out.is_open())
		while (getline(in, buf))
			out << ft_replace(buf, (std::string)av[2], (std::string)av[3]) << std::endl;
	else {
		std::cout << "Can't open the file !" << std::endl;
		return -1;
	}
	in.close();
	out.close();
	return 0;
}
