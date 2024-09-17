/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:31:20 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/15 17:15:30 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.class.hpp"

int	main(void) {
	//Bureaucrat test("Anne", 151);
//	Bureaucrat test2("Anne", 0);
	Bureaucrat test3("Annie", 150);
	Bureaucrat test4("David", 1);
	Bureaucrat test5("Boris", 50);

	
	
	std::cout << std::endl;

	std::cout << test5 << std::endl;
	
	std::cout << std::endl;

	std::cout << test3 << std::endl;
	test3.incrGrade();
	std::cout << test3 << std::endl;
	test3.decrGrade();
	test3.decrGrade();
	
	std::cout << std::endl;
		
	std::cout << test4 << std::endl;
	test4.incrGrade();
	
	std::cout << std::endl;
	return 0;
}
