/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:22 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/18 16:31:11 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.class.hpp"
#include <iostream>
#include <fstream>

PresidentialPardonForm::PresidentialPardonForm(void) {
	std::cout << "Constructor of PresidentialPardonForm" << std::endl;
	return ;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target): Form("Presidential", target, 25, 5) {
	std::cout << "Constructor of PresidentialPardonForm" << std::endl;
	return ;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& cpy) {
	*this = cpy;
	return ;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
	std::cout << "Destructor of PresidentialPardonForm" << std::endl;
	return ;
}

void PresidentialPardonForm::execute(Bureaucrat const& executor) const {
	(getGrsign() <= 25 && getExec() <= 5) ? std::cout << executor.getName() << "was forgiven by Zaphod Beeblebrox" << std::endl : throw Form::GradeTooLowException();
}

PresidentialPardonForm & PresidentialPardonForm::operator = (const PresidentialPardonForm& an) {
	(void) an;
	return *this;
}
