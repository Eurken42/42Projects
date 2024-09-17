/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:58 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/18 14:21:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_CLASS_HPP
# define BUREAUCRAT_CLASS_HPP

#include <iostream>
#include <string>
#include "Form.class.hpp"

class Form;

class Bureaucrat {
	public :
		Bureaucrat(void);
		Bureaucrat(std::string name, unsigned int grade);
		Bureaucrat(const Bureaucrat& cpy);
		~Bureaucrat(void);

		std::string getName(void) const;
		void signForm(Form& form) const;

		void incrGrade(void);
		void decrGrade(void);
		unsigned int getGrade(void) const;
		void setGrade(unsigned int grade);

		class GradeTooLowException: public std::exception {
			public :
				virtual const char* what() const throw() {
					return "Grade too Low !";
				}
		};

		class GradeTooHighException: public std::exception {
			public :
				virtual const char* what() const throw() {
					return "Grade too High !";
				}
		};

		Bureaucrat & operator = (const Bureaucrat& an);
	private :
		const std::string	name;
		unsigned int		grade;
};

std::ostream & operator << (std::ostream& os, const Bureaucrat &f);

#endif
