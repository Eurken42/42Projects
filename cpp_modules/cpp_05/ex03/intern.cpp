/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:32:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 16:12:27 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.class.hpp"
#include "RobotomyRequestForm.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include "PresidentialPardonForm.class.hpp"

Intern::Intern(void) {
	std::cout << "Constructor Intern" << std::endl;
	return ;
}
Intern::Intern(const Intern& cpy) {
	std::cout << "Constructor Intern" << std::endl;
	*this = cpy;
}

Intern::~Intern(void) {
	std::cout << "Destructor Intern" << std::endl;
	return ;
}

Form *Intern::makeForm(std::string name, std::string target) {
	Form *form_ret = NULL;
	t_form list[] = 
	{ 
		{ "robotomy request", new RobotomyRequestForm(target) },
		{ "presidential pardon", new PresidentialPardonForm(target) },
		{ "shrubbery creation", new ShrubberyCreationForm(target) }
	};
	int	i = -1;
	while (++i < 3) {
		if (list[i].f_name == name)
			form_ret = list[i].f_type;
		else
			delete list[i].f_type;
	}
	if (form_ret == NULL)
		std::cout << std::endl << "Form " << name << " doesn't exist !" << std::endl;
	else
		std::cout << std::endl << "Intern create " << name << std::endl;
	return (form_ret);
}
