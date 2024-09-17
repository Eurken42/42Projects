/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:32:26 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/29 14:15:01 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_hexa_count(unsigned int nb, int *count, int up)
{
	char	*hexa;

	if (up)
		hexa = "0123456789ABCDEF";
	else
		hexa = "0123456789abcdef";
	if (nb >= 0 && nb <= 15)
		ft_putchar_count(hexa[nb], count);
	else if (nb > 15)
	{
		ft_putnbr_hexa_count(nb / 16, count, up);
		ft_putnbr_hexa_count(nb % 16, count, up);
	}
}

/*int	main(void)
{
	int	i;
	int count = 50;

	i = 0;
	while (i >= -16)
	{
		ft_putnbr_hexa_count(i, &count);
		printf("\n");
		//printf("    VS     %d\n", i);
		i--;
	}
}*/
