/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:58:17 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/18 14:02:43 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_putnbr_hexa_ptr(long int nb)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb >= 0 && nb <= 15)
		ft_putchar(hexa[nb]);
	else if (nb > 15)
	{
		ft_putnbr_hexa_ptr(nb / 16);
		ft_putnbr_hexa_ptr(nb % 16);
	}
	else if (nb <= 0 && nb >= -15)
	{
		ft_putchar('-');
		ft_putchar(hexa[-nb]);
	}
	else if (nb < -15)
	{
		ft_putchar('-');
		ft_putnbr_hexa_ptr(-(nb / 16));
		ft_putnbr_hexa_ptr(-(nb % 16));
	}
}

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
