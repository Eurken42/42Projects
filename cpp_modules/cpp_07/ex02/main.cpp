/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:55:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/06 13:41:53 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.class.hpp"
#include <iostream>
/*
int main(void) {
	Array<int> a(5);
	Array<int> a2;
	Array<int> a3;

	a3 = a;
	std::cout << "A -> " << a.size() << std::endl;
	std::cout << "A2 -> " << a2.size() << std::endl;
	std::cout << "A3 -> " << a3.size() << std::endl;
	return 0;
}
*/
#define MAX_VAL 10
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
	Array<std::string> smth;
	Array<std::string> str(12);
	str[0] = "salut";
	str[11] = "salut2";
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
		std::cout << std::endl << "smth :" << std::endl << smth;
		std::cout << std::endl << "str :" << std::endl << str;
		std::cout << std::endl << "numbers :" << std::endl << numbers;
		std::cout << std::endl << "tmp :" << std::endl << tmp;
		std::cout << std::endl << "test :" << std::endl << test;
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "Try access -2" << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "Try access Max index +1" << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}
