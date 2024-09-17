/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:33:34 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 16:58:57 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.class.hpp"

Bureaucrat::Bureaucrat(void) {
	std::cout << "Constructor Bureaucrat" << std::endl;
	return ;
}

Bureaucrat::Bureaucrat(std::string name, unsigned int grade): name(name), grade(grade) {
	std::cout << "Constructor Bureaucrat" << std::endl;
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (grade > 150) 
		throw Bureaucrat::GradeTooLowException();
	return ;
}

Bureaucrat::Bureaucrat(const Bureaucrat& in): name(in.getName()), grade(in.getGrade()) {
	std::cout << "Copy constructor Bureaucrat" << std::endl;
	return ;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Destructor Bureaucrat" << std::endl;
	return ;
}

std::string Bureaucrat::getName(void) const {
	return this->name;
}

void Bureaucrat::signForm(Form& form) const {
	if (form.getSign() == true)
		std::cout << getName() << " signed " << form.getName() << std::endl;
	else	
		std::cout << getName() << " couldn't sign " << form.getName() << " because idc" << std::endl;
}

void Bureaucrat::executeForm(Form const & form) {
		std::cout << getName() << " executed " << form.getName() << std::endl;
}

void Bureaucrat::decrGrade(void) { 
	((this->grade + 1) > 150) ? throw Bureaucrat::GradeTooLowException() : this->grade = this->grade + 1;
	return ;
}

void Bureaucrat::incrGrade(void) {
	((this->grade - 1) < 1) ? throw Bureaucrat::GradeTooHighException() : this->grade = this->grade - 1;
	return ;
}

unsigned int Bureaucrat::getGrade(void) const {
	return this->grade;
}

void Bureaucrat::setGrade(unsigned int grade) {
	this->grade = grade;
}

Bureaucrat & Bureaucrat::operator = (const Bureaucrat& an) {
	this->grade = an.getGrade();
	return *this;
}

std::ostream & operator << (std::ostream& os, const Bureaucrat &f) {
	os << f.getName() << ", bureaucrat grade " << f.getGrade();
	return (os);
}
