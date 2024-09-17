/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.class.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:37:59 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 14:35:09 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_CLASS_HPP
# define SHRUBBERYCREATIONFORM_CLASS_HPP

#include "Form.class.hpp"
#include "Bureaucrat.class.hpp"

class ShrubberyCreationForm: public Form {
	public :
		ShrubberyCreationForm(void);
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm& cpy);
		~ShrubberyCreationForm(void);

		virtual void execute(Bureaucrat const & executor) const;
		ShrubberyCreationForm & operator = (const ShrubberyCreationForm& an);
};

#endif
