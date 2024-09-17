/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:43:10 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/04 14:25:54 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
 
int  main(int ac, char **av)
{
    if (ac > 1)
        for (int i = 1; i < ac; i++)
            for (size_t j = 0; j < strlen(av[i]); j++)
                std::cout << (char)toupper(av[i][j]);
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    std::cout << std::endl;
    return (0);
}
