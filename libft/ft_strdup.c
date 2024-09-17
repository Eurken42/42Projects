/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:54:14 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 16:50:15 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
        La fonction strdup() renvoie un pointeur sur une nouvelle chaîne 
        de caractères qui est dupliquée depuis s. La mémoire occupée par
		cette nouvelle chaîne est obtenue en appelant malloc(3), et peut
		(doit) donc être libérée avec free(3).

    VALEUR RENVOYÉE
        La fonction strdup() renvoie un pointeur sur la chaîne dupliquée, 
		ou NULL s'il n'y avait pas assez de mémoire.  
*/

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	i = 0;
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
