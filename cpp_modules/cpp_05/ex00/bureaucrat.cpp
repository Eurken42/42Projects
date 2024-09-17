/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:33:34 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/15 17:15:28 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.class.hpp"

Bureaucrat::Bureaucrat(void) {
	std::cout << "Constructor Bureaucrat" << std::endl;
	return ;
}

Bureaucrat::Bureaucrat(std::string name, unsigned int grade): name(name) {
	std::cout << "Constructor Bureaucrat" << std::endl;
	try {
		(grade < 1) ? throw std::runtime_error("High") : (grade > 150) ? throw std::runtime_error("Low") : this->grade = grade;
	}
	catch (std::exception& e) {
		std::cout << "Bureaucrat::GradeToo" << e.what() << "Exception" << std::endl;
	}
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

void Bureaucrat::decrGrade(void) { 
	try {
		((this->grade + 1) > 150) ? throw std::runtime_error("Low") : this->grade = this->grade + 1;
	}
	catch (std::exception& e) {
		std::cout << "Bureaucrat::GradeToo" << e.what() << "Exception" << std::endl;
	}
	return ;
}

void Bureaucrat::incrGrade(void) {
	try {
		((this->grade - 1) < 1) ? throw std::runtime_error("High") : this->grade = this->grade - 1;
	}
	catch (std::exception& e) {
		std::cout << "Bureaucrat::GradeToo" << e.what() << "Exception" << std::endl;
	}
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
