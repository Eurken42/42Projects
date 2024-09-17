/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:16:12 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/15 16:49:00 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *src, char const *set)
{
	int				start;
	int				end;
	int				i;
	unsigned int	size;

	i = 0;
	if (!src || !set)
		return (NULL);
	while (src[i] && ft_set(src[i], set))
		i++;
	start = i;
	i = ft_strlen(src) - 1;
	while (i > 0 && ft_set(src[i], set))
		i--;
	end = i;
	size = end - start + 1;
	return (ft_substr(src, start, size));
}
