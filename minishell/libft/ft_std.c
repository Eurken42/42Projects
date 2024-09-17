/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:48:45 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/15 14:33:44 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

int	ft_atoi(const char *s)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r' || *s == ' '
		|| *s == '\f')
		++s;
	if (*s == '-')
		sign = -1;
	s += (*s == '-' || *s == '+');
	while (ft_isdigit(*s))
	{
		if (sign * n > INT_MAX / 10 || (sign * n == INT_MAX / 10 && (*(s + 1)
					|| (*s > '8' && sign < 0) || (*s > '7' && sign > 0))))
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		n = n * 10 + (*s - '0') * sign;
		++s;
	}
	return (n);
}

static unsigned int	ft_itoa_init(int n, size_t *len, int *neg)
{
	unsigned int	nbr;

	*len = 1;
	*neg = 0;
	if (n < 0)
	{
		*neg = 1;
		++*len;
		nbr = (unsigned int)((n + 1) * -1) + 1;
	}
	else
		nbr = (unsigned int)n;
	n /= 10;
	while (n)
	{
		n /= 10;
		++*len;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	size_t			len;
	unsigned int	nbr;
	int				neg;
	char			*str;

	nbr = ft_itoa_init(n, &len, &neg);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (neg)
	{
		*str++ = '-';
		--len;
	}
	while (len)
	{
		str[len - 1] = '0' + nbr % 10;
		nbr /= 10;
		--len;
	}
	return (str - neg);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (!count || !size)
		return (malloc(0));
	if (count > (SIZE_MAX / size + (SIZE_MAX % size > 0)))
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}
