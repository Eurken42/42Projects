/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:56:49 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/16 13:43:12 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;
	size_t	index;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)ft_strlen(s) > len)
		index = len;
	else
		index = (size_t)ft_strlen(s);
	d = (char *) malloc((index + 1) * sizeof(char));
	if (!d || !s)
		return (NULL);
	while (start < (unsigned int)ft_strlen(s) && i < index)
		d[i++] = s[start++];
	d[i] = '\0';
	return (d);
}
