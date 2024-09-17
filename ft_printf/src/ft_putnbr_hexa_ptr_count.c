/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:58:17 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/29 12:02:54 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_hexa_ptr_count(unsigned long int nb, int *count)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb >= 0 && nb <= 15)
		ft_putchar_count(hexa[nb], count);
	else if (nb > 15)
	{
		ft_putnbr_hexa_ptr_count(nb / 16, count);
		ft_putnbr_hexa_ptr_count(nb % 16, count);
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
