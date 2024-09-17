/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:25:26 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 16:50:27 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
        La fonction atoi() convertit le début de la chaîne pointée par nptr 
		en entier de type int

    VALEUR RENVOYÉE
        Le résultat de la conversion.  
*/

int	ft_atoi(const char *nptr)
{
	int	neg;
	int	res;
	int	i;

	i = 0;
	neg = 1;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			neg *= -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * neg);
}

/*int main(int ac, char *av[])
{
    (void) ac;

    printf("RES : %d\nREAL : %d\n", ft_atoi(av[1]), atoi(av[1]));
    return (0);
}*/
