/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:30:51 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 19:57:13 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include <libft.h>
#include <stdlib.h>

char	*ft_itoaw(int nbr, unsigned int min_len, unsigned int min_digit)
{
	char	*conv;
	char	*str;
	size_t	len;
	int		neg;

	str = ft_itoa(nbr);
	len = ft_strlen(str);
	neg = 0;
	if (nbr < 0)
		neg = 1;
	if (min_digit + neg > min_len)
		min_len = min_digit + neg;
	if (len < min_len)
	{
		conv = ft_calloc(min_len + 1, sizeof(char));
		if (!conv)
			return (NULL);
		if (neg)
			conv[0] = '-';
		ft_memcpy(conv + neg + min_len - len, str + neg, len - neg);
		ft_memset(conv + neg, '0', min_len - len);
		free(str);
		return (conv);
	}
	return (str);
}

char	*ft_uitoa(unsigned int u, unsigned int min_len)
{
	char			*str;
	unsigned int	nbr;
	size_t			len;

	len = 1;
	nbr = u / 10;
	while (nbr)
	{
		++len;
		nbr /= 10;
	}
	if (min_len > len)
		len = min_len;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (len)
	{
		str[--len] = '0' + u % 10;
		u /= 10;
	}
	return (str);
}

static char	ft_dtohex(int digit, int up)
{
	if (digit >= 10)
	{
		if (up)
			return ('A' + digit - 10);
		else
			return ('a' + digit - 10);
	}
	else
		return ('0' + digit);
}

char	*ft_ultohex(unsigned long long ul, int up, unsigned int min_len)
{
	char				*str;
	unsigned long long	nbr;
	size_t				len;

	len = 1;
	nbr = ul / 16;
	while (nbr)
	{
		++len;
		nbr /= 16;
	}
	if (min_len > len)
		len = min_len;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (len)
	{
		str[--len] = ft_dtohex(ul % 16, up);
		ul /= 16;
	}
	return (str);
}
