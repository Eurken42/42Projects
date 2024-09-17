/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:56:49 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 15:47:39 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.class.hpp"
#include <iostream>
#include <fstream>

RobotomyRequestForm::RobotomyRequestForm(void) {
	//std::cout << "Constructor of RobotomyRequestForm" << std::endl;
	return ;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): Form("Robotomy", target, 72, 45) {
	//std::cout << "Constructor of RobotomyRequestForm" << std::endl;
	return ;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& cpy) {
	*this = cpy;
	return ;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
	std::cout << "Destructor of RobotomyRequestForm" << std::endl;
	return ;
}

void RobotomyRequestForm::execute(Bureaucrat const& executor) const {
	if (getGrsign() <= 72 && getExec() <= 45) {
		std::cout << "Boom boom la perceuse" << std::endl << executor.getName();
		srand(time(NULL));
		((rand() % 10) <= 4) ? std::cout << executor.getName() << "Robotised" : std::cout << " Fail";
		std::cout << std::endl;
	} else
		throw Form::GradeTooLowException();
}

RobotomyRequestForm & RobotomyRequestForm::operator = (const RobotomyRequestForm& an) {
	(void) an;
	return *this;
}
