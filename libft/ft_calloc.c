/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:00:13 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 13:20:59 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;
	int		tot_size;

	tot_size = nmemb * size;
	new = malloc(tot_size);
	if (!new)
		return (NULL);
	ft_memset(new, 0, tot_size);
	return (new);
}
