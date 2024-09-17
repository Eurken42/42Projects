/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:21:28 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/15 19:00:51 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_fill_min(int len)
{
	char	*s;
	char	*num;
	int		i;

	i = -1;
	num = "-2147483648";
	s = (char *) malloc(len * sizeof(char));
	if (!s)
		return (NULL);
	while (num[++i])
		s[i] = num[i];
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
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
		return (ft_fill_min(11));
	else if (n <= 0)
	{
		flag = 1;
		n *= -1;
		int_len++;
	}
	backup = n;
	int_len = ft_len_10(int_len, n);
	d = ft_create_malloc(int_len, n);
	if (!d)
		return (NULL);
	if (flag == 1)
		d[i++] = '-';
	return (ft_fill_tab(backup, d, i, int_len));
}
