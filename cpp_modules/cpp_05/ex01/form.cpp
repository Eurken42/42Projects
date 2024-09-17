/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:54:46 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/16 18:06:29 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.class.hpp"
#include <exception>

//Constructor / Destructor

Form::Form(void): grsign(50), exec(50) {
	std::cout << "Constructor Form" << std::endl;
	return ;
}

Form::Form(const std::string name, const unsigned int grsign, const unsigned int exec): sign(false), name(name), grsign(grsign), exec(exec) {
	std::cout << "Constructor Form" << std::endl;
	if (grsign < 1 || exec < 1)
		throw Form::GradeTooHighException();
	if (grsign > 150 || exec > 150)
		throw Form::GradeTooLowException();
	return ;
}

Form::Form(const Form& cpy): sign(false), name(cpy.name), grsign(cpy.grsign), exec(cpy.exec) {
	std::cout << "Copy constructor Form" << std::endl;
	return;
}

Form::~Form(void) {
	std::cout << "Destructor Form" << std::endl;
	return ;
}

//end Constructor / Destructor

//Getter

bool Form::getSign(void) const {
	return this->sign;
}

std::string Form::getName(void) const {
	return this->name;
}

unsigned int Form::getGrsign(void) const {
	return this->grsign;
}

unsigned int Form::getExec(void) const {
	return this->exec;
}

//end Getter

void Form::beSigned(const Bureaucrat& bur) {
	(bur.getGrade() > getGrsign()) ? throw Form::GradeTooLowException() : this->sign = true;
}

Form & Form::operator = (const Form& an) {
	(void) an;
	return *this;
}

std::ostream & operator << (std::ostream& os, const Form &f) {
	os << "Sign: " << f.getSign() << " Name: " << f.getName() << " Sign grade: " << f.getGrsign() << " Exec grade: " << f.getExec();
	return os;
}
