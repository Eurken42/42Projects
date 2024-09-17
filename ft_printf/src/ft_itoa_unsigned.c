/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:21:28 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/29 14:19:25 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_create_malloc_us(unsigned int len, unsigned int n)
{
	char	*d;

	if (n == 0)
		len++;
	if (n == -0)
		len--;
	d = (char *) malloc((len + 1) * sizeof(char));
	if (!d)
		return (NULL);
	return (d);
}

unsigned int	ft_len_10_us(unsigned int int_len, unsigned int n)
{
	while (n > 0)
	{
		n /= 10;
		int_len++;
	}
	return (int_len);
}

char	*ft_fill(unsigned int n, char *d, unsigned int i, unsigned int len)
{
	if (n != 0)
	{
		while (n > 0)
		{
			d[--len] = (n % 10) + '0';
			n /= 10;
			i++;
		}
	}
	else
	{
		i = 0;
		d[i] = '0';
		i++;
	}
	d[i] = '\0';
	return (d);
}

void	ft_itoa_unsigned(unsigned int n, int *count)
{
	unsigned int		int_len;
	char				*d;
	unsigned int		i;
	unsigned int		backup;

	i = 0;
	int_len = 0;
	backup = n;
	int_len = ft_len_10_us(int_len, n);
	d = ft_create_malloc_us(int_len, n);
	if (!d)
		return ;
	d = ft_fill(backup, d, i, int_len);
	ft_putstr_count(d, count);
	free(d);
}
