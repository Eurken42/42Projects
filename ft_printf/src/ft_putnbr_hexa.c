/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:32:26 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/18 16:51:26 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_hexa(int nb)
{
	char	*hexa;

	hexa = "0123456789ABCDEF";
	if (nb >= 0 && nb <= 15)
		ft_putchar(hexa[nb]);
	else if (nb > 15)
	{
		ft_putnbr_hexa(nb / 16);
		ft_putnbr_hexa(nb % 16);
	}
	else if (nb <= 0 && nb >= -15)
	{
		ft_putchar('-');
		ft_putchar(hexa[-nb]);
	}
	else if (nb < -15)
	{
		ft_putchar('-');
		ft_putnbr_hexa(-(nb / 16));
		ft_putnbr_hexa(-(nb % 16));
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
