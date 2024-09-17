/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:13:53 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 13:08:45 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*#include <stdio.h>
int main(int ac, char *av[])
{
    (void) ac;

    if (ft_isalpha(av[1][0]) == 1)
        printf("Alpha !");
    else
        printf("Not alpha !");
    return (0);
}*/
