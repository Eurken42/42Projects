/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:31:20 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/16 18:02:39 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.class.hpp"
#include "Form.class.hpp"

int	main(void) {
	/*Bureaucrat test("Anne", 151);
	Bureaucrat test2("Anne", 0);
	Bureaucrat test3("Annie", 150);
	Bureaucrat test4("David", 1);
	*/
	Form		a("A13", 150, 6);
	Form		a1("A31", 1, 6);
	Form		a2("A122223", 10, 6);

	const Bureaucrat test("Boris", 50);
	const Bureaucrat test1("Denis", 10);

	std::cout << std::endl << a << std::endl;

	a.beSigned(test);
	test.signForm(a);
	
	std::cout << a << std::endl;
	
	/*std::cout << std::endl;

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


*/	std::cout << std::endl;
	return 0;
}

/*
std::cout << std::endl;
	std::cout << "CONSTRUCTING:" << std::endl;
	std::cout << "----------------------------" << std::endl;
	Bureaucrat	bob("Bob", 1);
	Bureaucrat	bill("Bill", 132);

	Bureaucrat & bob_ref = bob;
	Bureaucrat & bill_ref = bill;

	Form		a("A13", 4, 6);
	Form		b("B97", 146, 135);

	// Create a Form with grades too low
	try
	{
		Form	c("C46", 489, 1435);
	}
	catch (Form::Exception &e)
	{
		std::cout << "Constructor failure: " << e.what() << std::endl; //the grade is too low
	}

	// Create a grade with grades too high
	try
	{
		Form	c("D143", -583, -800);
	}
	catch (Form::Exception &e)
	{
		std::cout << "Constructor failure: " << e.what() << std::endl; //the grade is too high
	}
	std::cout << std::endl << std::endl;

	// Sign forms
	std::cout << std::endl;
	std::cout << "SIGN FORMS:" << std::endl;
	std::cout << "----------------------------" << std::endl;

	// Sign OK
	std::cout << "SIGN OK:" << std::endl;
	bob_ref.signForm(a);
	std::cout << a << " just showed its current status" << std::endl;
	a.setSigned(false);
	std::cout << std::endl << std::endl;

	// Sign KO
	std::cout << "SIGN KO:" << std::endl;
	bill_ref.signForm(a);
	std::cout << a << " just showed its current status" << std::endl;
	std::cout << std::endl << std::endl;

	// Sign OK
	std::cout << "SIGN OK:" << std::endl;
	bob.signForm(b);
	std::cout << b << " just showed its current status" << std::endl;
	b.setSigned(false);
	std::cout << std::endl << std::endl;
	
	// Sign OK
	std::cout << "SIGN OK:" << std::endl;
	bill.signForm(b);
	std::cout << b << " just showed its current status" << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << std::endl;
	std::cout << "DESTRUCTORS:" << std::endl;
	std::cout << "----------------------------" << std::endl;
	return (0);
	*/
