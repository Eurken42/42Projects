/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:43:27 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 16:40:43 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
        La fonction strrchr() renvoie un pointeur sur la dernière 
		occurrence du caractère c dans la chaîne s.

    VALEUR RENVOYÉE
        Renvoi un pointeur sur le caractère correspondant, ou NULL 
		si le caractère n'a pas été trouvé
*/

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	b = (char *)s;
	i = ft_strlen(b) - 1;
	if (c == '\0')
		return (b + i + 1);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (b + i);
		i--;
	}
	return (NULL);
}
