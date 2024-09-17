/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:29:44 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 14:02:20 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
        La fonction memchr() examine les n premiers octets de la zone mémoire 
		pointée par s à la recherche du caractère c. Le premier octet 
		correspondant à c (interprété comme un unsigned char) arrête 
		l'opération.

    VALEUR RENVOYÉE
        Les fonctions memchr() et memrchr() renvoient un pointeur sur l'octet
		correspondant, ou NULL si le caractère n'est pas présent dans la zone
		de mémoire concernée.  
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*b;
	size_t			i;

	b = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (b[i] == (unsigned char)c)
			return (b + i);
		i++;
	}
	return (NULL);
}
