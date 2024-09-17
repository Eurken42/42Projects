/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:04:14 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/05 18:21:11 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*map;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	map = ft_calloc(len + 1, sizeof(char));
	if (!map)
		return (NULL);
	while (i < len)
	{
		map[i] = (*f)(i, s[i]);
		++i;
	}
	return (map);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (*s)
	{
		(*f)(i, s);
		++s;
		++i;
	}
}
