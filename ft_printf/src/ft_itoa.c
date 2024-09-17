/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:21:28 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/18 16:47:49 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_create_malloc(int len, int n)
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

int	ft_len_10(int int_len, int n)
{
	while (n > 0)
	{
		n /= 10;
		int_len++;
	}
	return (int_len);
}

char	*ft_fill_tab(int n, char *d, int i, int int_len)
{
	if (n != 0)
	{
		while (n > 0)
		{
			d[--int_len] = (n % 10) + '0';
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

void	ft_fill_min(int len, int *count)
{
	char	*s;
	char	*num;
	int		i;

	i = -1;
	num = "-2147483648";
	s = (char *) malloc(len * sizeof(char));
	if (!s)
		return ;
	while (num[++i])
		s[i] = num[i];
	s[i] = '\0';
	ft_putstr_count(s, count);
	free(s);
}

void	ft_itoa(int n, int *count)
{
	int		int_len;
	char	*d;
	int		flag;
	int		i;
	int		backup;

	i = 0;
	int_len = 0;
	flag = 0;
	if (n == -2147483648)
		ft_fill_min(11, count);
	else if (n <= 0)
	{
		flag = 1;
		n *= -1;
		int_len++;
	}
	backup = n;
	int_len = ft_len_10(int_len, n);
	d = ft_create_malloc(int_len, n);
	if (flag == 1)
		d[i++] = '-';
	d = ft_fill_tab(backup, d, i, int_len);
	ft_putstr_count(d, count);
	free(d);
}
