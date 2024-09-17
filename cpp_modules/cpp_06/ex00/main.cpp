/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:13:27 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/30 15:52:29 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include <string>
#include <limits.h>
#include "Main.class.hpp"

int ft_isdigit(std::string input) {
	size_t i = -1;

	if (input[0] == '-' || input[0] == '+')
		i++;
	while (++i < input.length()) {
		if (!std::isdigit(input[i]))
			return 0;
	}
	return 1;
}

int ft_isfloat(std::string input) {
	size_t i = -1;

	if (input[0] == '-' || input[0] == '+')
		i++;
	while (++i < input.length()) {
		if (i == (input.length() - 1) && input[i] == 'f')
			return _Float;
		if (!std::isdigit(input[i]) && input[i] != '.')
			return _UNKNOWN;
	}
	return _Double;
}

int	getType(std::string input) {
	size_t fnd;

	if (input.length() == 1 && !std::isdigit(input[0]))
		return _Char;
	if (!std::isdigit(input[0]) && input[0] != '-' && input[0] != '+')
		return _UNKNOWN;
	fnd = input.find(".");
	if (fnd == 0 || fnd == (input.length() - 1))
		return _UNKNOWN;
	else if (fnd == std::string::npos && ft_isdigit(input) == 1)
		return _Int;
	fnd = input.find(".", fnd + 1);
	if (fnd != std::string::npos)
		return _UNKNOWN;
	return (ft_isfloat(input));
}

int getPrecision(std::string const &input, int num) {
	return (input.length() - (int)input.find(".") - num);
}

void fromChar(std::string const &input) {
	char nb = input[0];
	
	std::cout << "Char !" << std::endl << std::endl;
	if (nb < 0 || nb > 127)
		std::cout << "char: impossible" << std::endl;
	else if (nb < 32 || nb > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << "'" << static_cast<char>(nb) << "'" << std::endl;
	if (nb > static_cast<double>(INT_MAX) || nb < static_cast<double>(INT_MIN))
		std::cout << "int: overflow" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(nb) << std::endl;
	if (getPrecision(input, 2) > 0) {
		std::cout << std::fixed << std::setprecision(getPrecision(input, 2));
		std::cout << "float: " << static_cast<float>(nb) << "f" << std::endl;
	} else
		std::cout << "float: " << static_cast<float>(nb) << std::endl;
	std::cout << "double: " << static_cast<double>(nb) << std::endl;
}

void fromInt(std::string const &input) {
	double nb = std::strtod(input.c_str(), NULL);
	
	std::cout << "Int !" << std::endl << std::endl;
	if (nb < 0 || nb > 127)
		std::cout << "char: impossible" << std::endl;
	else if (nb < 32 || nb > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << "'" << static_cast<char>(nb) << "'" << std::endl;
	if (nb > static_cast<double>(INT_MAX) || nb < static_cast<double>(INT_MIN))
		std::cout << "int: overflow" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(nb) << std::endl;
	std::cout << "float: " << static_cast<float>(nb) << std::endl;
	std::cout << "double: " << static_cast<double>(nb) << std::endl;
}

void fromFloat(std::string const &input) {
	float nb = std::stof(input.c_str(), NULL);

	std::cout << "Float !" << std::endl << std::endl;
	if (nb < 0 || nb > 127)
		std::cout << "char: impossible" << std::endl;
	else if (nb < 32 || nb > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << "'" << static_cast<char>(nb) << "'" << std::endl;
	if (nb > static_cast<double>(INT_MAX) || nb < static_cast<double>(INT_MIN))
		std::cout << "int: overflow" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(nb) << std::endl;
	if (getPrecision(input, 2) > 0) {
		std::cout << std::fixed << std::setprecision(getPrecision(input, 2));
		std::cout << "float: " << static_cast<float>(nb) << "f" << std::endl;
	} else
		std::cout << "float: " << static_cast<float>(nb) << std::endl;
	std::cout << "double: " << static_cast<double>(nb) << std::endl;
}

void fromDouble(std::string const &input) {
	double nb = std::strtod(input.c_str(), NULL);

	std::cout << "Double !" << std::endl << std::endl;
	if (nb < 0 || nb > 127)
		std::cout << "char: impossible" << std::endl;
	else if (nb < 32 || nb > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << "'" << static_cast<char>(nb) << "'" << std::endl;
	if (nb > static_cast<double>(INT_MAX) || nb < static_cast<double>(INT_MIN))
		std::cout << "int: overflow" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(nb) << std::endl;
	if (getPrecision(input, 1) > 0) {
		std::cout << std::fixed << std::setprecision(getPrecision(input, 1));
		std::cout << "float: " << static_cast<float>(nb) << "f" << std::endl;
	} else
		std::cout << "float: " << static_cast<float>(nb) << std::endl;
	std::cout << "double: " << static_cast<double>(nb) << std::endl;
}

int	main(int ac, char **av) {
	int type;
	std::string input;
	
	if (ac != 2) {
		std::cout << "Args error : (" << std::endl;
		return -1;
	}
	input = (std::string)av[1];
	type = getType(input);
	if (input == "-inff" || input == "+inff" || input == "nanf" || input == "-inf" || input == "+inf" || input == "nan") {
		double d = strtod(input.c_str(), NULL);
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
		std::cout << "double: " << static_cast<double>(d) << std::endl;
	} else if (type == _Char)
		fromChar(input);
	else if (type == _Int)
		fromInt(input);
	else if (type == _Float)
		fromFloat(input);
	else if (type == _Double)
		fromDouble(input);
	else if (type == _UNKNOWN) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	return 0;
}
