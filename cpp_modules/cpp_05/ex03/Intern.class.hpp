/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:30:15 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 16:12:26 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_CLASS_HPP
# define INTERN_CLASS_HPP

#include "Form.class.hpp"
#include <iostream>

class Intern {
	public :
		Intern(void);
		Intern(const Intern& cpy);
		~Intern(void);

		Form *makeForm(std::string name, std::string target);
};

typedef struct s_form {
	std::string f_name;
	Form *f_type;
}	t_form;

#endif
