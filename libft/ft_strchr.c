/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:39:04 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/11 13:02:36 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
        La fonction strchr() renvoie un pointeur sur la première occurrence
		du caractère c dans la chaîne s.

    VALEUR RENVOYÉE
        Renvoi un pointeur sur le caractère correspondant, ou NULL si le
		caractère n'a pas été trouvé
*/

char	*ft_strchr(const char *s, int c)
{
	char	*b;
	int		i;

	i = -1;
	b = (char *)s;
	while (b[++i])
		if (b[i] == (char)c)
			return (b + i);
	if (!c)
		return (b + i);
	return (NULL);
}
