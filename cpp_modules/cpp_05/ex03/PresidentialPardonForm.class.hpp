/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.class.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:37:59 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 14:34:28 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_CLASS_HPP
# define PRESIDENTIALPARDONFORM_CLASS_HPP

#include "Form.class.hpp"
#include "Bureaucrat.class.hpp"

class PresidentialPardonForm: public Form {
	public :
		PresidentialPardonForm(void);
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(const PresidentialPardonForm& cpy);
		~PresidentialPardonForm(void);

		virtual void execute(Bureaucrat const & executor) const;
		PresidentialPardonForm & operator = (const PresidentialPardonForm& an);
};

#endif
