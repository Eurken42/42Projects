/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:31:20 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:08 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.class.hpp"
#include "Form.class.hpp"
#include "Intern.class.hpp"

int	main(void) {
	Bureaucrat test4("David", 6);
	
	Intern someRandomIntern;
	Form* rrf;
	
	std::cout << std::endl;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	rrf->execute(test4);
	if (rrf)
		delete rrf;

	std::cout << std::endl;
	rrf = someRandomIntern.makeForm("presidential pardon", "Bende12d121dr");
	rrf->execute(test4);
	if (rrf)
		delete rrf;

	std::cout << std::endl;
	rrf = someRandomIntern.makeForm("shrubbery creation", "Bendererrere");
	rrf->execute(test4);
	if (rrf)
		delete rrf;

	std::cout << std::endl;
	rrf = someRandomIntern.makeForm("shrubbikdashdgahdery creation", "Bendererrere");
	if (rrf) {
		rrf->execute(test4);
		delete rrf;
	}

	std::cout << std::endl;
	return 0;
}
