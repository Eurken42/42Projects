/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:04:20 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 14:03:06 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
        La fonction memcpy() copie n octets depuis la zone mémoire src vers 
		la zone mémoire dest. Les deux zones ne doivent pas se chevaucher. 
		Si c'est le cas, utilisez plutôt memmove(3).  
    
    VALEUR RENVOYÉE
        La fonction memcpy() renvoie un pointeur sur dest.  
*/

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	unsigned const char	*src;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	dest = (unsigned char *) s1;
	src = (unsigned const char *) s2;
	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
