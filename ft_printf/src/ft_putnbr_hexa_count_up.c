/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:32:26 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/29 13:28:49 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*void	ft_putnbr_hexa_count_up(unsigned int nb, int *count)
{
	char	*hexa;

	hexa = "0123456789ABCDEF";
	if (nb >= 0 && nb <= 15)
		ft_putchar_count(hexa[nb], count);
	else if (nb > 15)
	{
		ft_putnbr_hexa_count(nb / 16, count);
		ft_putnbr_hexa_count(nb % 16, count);
	}
	else if (nb <= 0 && nb >= -15)
	{
		ft_putchar_count('-', count);
		ft_putchar_count(hexa[-nb], count);
	}
	else if (nb < -15)
	{
		ft_putchar_count('-', count);
		ft_putnbr_hexa_count(-(nb / 16), count);
		ft_putnbr_hexa_count(-(nb % 16), count);
	}
}*/

/*int	main(void)
{
	int	i;

	i = -10020;
	while (i <= -10000)
	{
		ft_putnbr_hexa(i);
		printf("    VS     %d\n", i);
		i++;
	}
}*/
