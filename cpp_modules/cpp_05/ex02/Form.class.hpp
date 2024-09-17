/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:24 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/18 16:23:25 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_CLASS_HPP
# define FORM_CLASS_HPP

#include <string>
#include <iostream>

#include "Bureaucrat.class.hpp"
class Bureaucrat;

class Form {
	public :
		Form(void);
		Form(const std::string name, std::string target, const unsigned int grsign, const unsigned int exec);
		Form(const Form& cpy);
		~Form(void);

		bool getSign(void) const;
		std::string getName(void) const;
		unsigned int getGrsign(void) const;
		unsigned int getExec(void) const;

		void beSigned(const Bureaucrat& bur);
		virtual void execute(Bureaucrat const & executor) const = 0;
		Form & operator = (const Form& an);

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
	private :
		bool sign;
		const std::string name;
		const std::string target;
		const unsigned int grsign;
		const unsigned int exec;
};

std::ostream & operator << (std::ostream& os, const Form &f);

#endif
