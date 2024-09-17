/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.class.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:37:59 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 14:35:23 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_CLASS_HPP
# define ROBOTOMYREQUESTFORM_CLASS_HPP

#include "Form.class.hpp"
#include "Bureaucrat.class.hpp"

class RobotomyRequestForm: public Form {
	public :
		RobotomyRequestForm(void);
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm& cpy);
		~RobotomyRequestForm(void);

		virtual void execute(Bureaucrat const & executor) const;
		RobotomyRequestForm & operator = (const RobotomyRequestForm& an);
};

#endif
