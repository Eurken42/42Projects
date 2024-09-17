/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:30:26 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/07 14:39:05 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.class.hpp"
#include <iostream>
#define MAX_VAL 100

int main(void) {
	Span sp = Span(100);

/*	srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        sp.addNumber(value);
    }*/
	
	/*sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);*/

	sp.addNumber(-100);
	sp.addNumber(40);
	sp.addNumber(39);
	sp.addNumber(37);
	sp.addNumber(33);
	sp.addNumber(23);
	sp.addNumber(13);
	sp.addNumber(13);
	sp.addNumber(34);
	sp.addNumber(23);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp << std::endl;
	return 0;
}
