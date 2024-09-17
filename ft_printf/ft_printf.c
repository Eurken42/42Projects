/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:48:35 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/29 14:15:32 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_arg(const char *str_in, int *i, int *count, char *arg)
{
	*i += 1;
	if (str_in[*i] == 'c')
		ft_putchar_count((char)arg, count);
	else if (str_in[*i] == 's')
		ft_putstr_count(arg, count);
	else if (str_in[*i] == 'd' || str_in[*i] == 'i')
		ft_itoa((int)arg, count);
	else if (str_in[*i] == 'u')
		ft_itoa_unsigned((unsigned int)arg, count);
	else if (str_in[*i] == 'x')
		ft_putnbr_hexa_count((unsigned int)arg, count, 0);
	else if (str_in[*i] == 'X')
		ft_putnbr_hexa_count((unsigned int)arg, count, 1);
	else if (str_in[*i] == 'p')
	{
		ft_putstr_count("0x", count);
		ft_putnbr_hexa_ptr_count((unsigned long int)arg, count);
	}
	else if (str_in[*i] == '%')
		ft_putchar_count('%', count);
	*i += 1;
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
			convert_arg(format, &i, &count, va_arg(args, char *));
		else
		{
			if (format[i] == '%' && format[i + 1] == '%')
				i++;
			ft_putchar_count(format[i], &count);
			i++;
		}
	}
	va_end(args);
	return (count);
}

/*int    main(void)
{
   char    *car;

    car = "aujourdhui";
    ft_printf("CHAR : %c\n", car[7]);
	ft_printf("STRING: %s\n", car);
	ft_printf("INT d vs i : %d vs %i\n", -750, 750);
	ft_printf("POURCENT : %%\n");
	ft_printf("unsigned int : %u\n", 4294967295);
	ft_printf("Adresse %p\n", &car);
	ft_printf(" %s", "SALUT");
	return (0);
}*/
