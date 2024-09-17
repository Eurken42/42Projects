/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:07:22 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/11 12:38:38 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*d;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	d = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (s[++i])
		d[i] = f(i, s[i]);
	d[i] = '\0';
	return (d);
}
