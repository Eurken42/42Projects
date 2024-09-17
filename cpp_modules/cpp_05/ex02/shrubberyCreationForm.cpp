/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:43:37 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/18 16:28:04 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.class.hpp"
#include <iostream>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(void) {
	std::cout << "Constructor of ShrubberyCreationForm" << std::endl;
	return ;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): Form("Shrubbery", target, 145, 137) {
	std::cout << "Constructor of ShrubberyCreationForm" << std::endl;
	return ;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& cpy) {
	*this = cpy;
	return ;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	std::cout << "Destructor of ShrubberyCreationForm" << std::endl;
	return ;
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
	if (getGrsign() <= 145 && getExec() <= 137) {	
		std::ofstream out;
		std::string new_file = executor.getName() + "_shrubbery";
		std::string tree = "                                   .         ;\n"
						   "      .              .              ;%     ;;\n"
 						   "        ,           ,                :;%  %;\n"
 						   "		:         ;                   :;%;'     .,\n"
 						   ",.        %;     %;            ;        %;'    ,;\n"
 						   "  ;       ;%;  %%;        ,     %;    ;%;    ,%'\n"
 						   "   %;       %;%;      ,  ;       %;  ;%;   ,%;'\n"
 						   "    ;%;      %;        ;%;        % ;%;  ,%;'\n"
 						   "     `%;.     ;%;     %;'         `;%%;.%;'\n"
 						   "      `:;%.    ;%%. %@;        %; ;@%;%'\n"
 						   "         `:%;.  :;bd%;          %;@%;'\n"
 						   "           `@%:.  :;%.         ;@@%;'\n"
 						   "             `@%.  `;@%.      ;@@%;\n"
 						   "			 `@%%. `@%%    ;@@%;\n"
 						   "                 ;@%. :@%%  %@@%;\n"
 						   "                   %@bd%%%bd%%:;\n"
 						   "                     #@%%%%%:;;\n"
 						   "                     %@@%%%::;\n"
 						   "                     %@@@%(o);  . '\n"
 						   "					 %@@@o%;:(.,'\n"
 						   "                  .. %@@@o%::;\n"
 						   "                    `)@@@o%::;\n"
 						   "                     %@@(o)::;\n"
 						   "                    .%@@@@%::;\n"
 						   "                    ;%@@@@%::;.\n"
 						   "                   ;%@@@@%%:;;;.\n"
 						   "               ...;%@@@@@%%:;;;;,..\n" 
						   "------------------------------------------------";
		out.open(new_file);
		(out.is_open()) ? out << tree : std::cout << "Can't open the file" << std::endl;
	} else
		throw Form::GradeTooLowException();
}

ShrubberyCreationForm & ShrubberyCreationForm::operator = (const ShrubberyCreationForm& an) {
	(void) an;
	return *this;
}
