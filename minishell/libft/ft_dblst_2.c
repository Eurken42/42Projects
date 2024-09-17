/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblst_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:11:22 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/06 13:12:01 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ltoa(t_dblst *lst)
{
	char	**ar;
	int		i;

	ar = ft_calloc(ft_dblst_size(lst) + 1, sizeof(*ar));
	i = 0;
	while (lst)
	{
		ar[i] = ft_strdup(lst->content);
		++i;
		lst = lst->next;
	}
	return (ar);
}

t_dblst	*ft_atol(char **ar)
{
	t_dblst	*lst;
	t_dblst	*new;

	lst = NULL;
	while (*ar)
	{
		new = ft_dblst_new(ft_strdup(*ar));
		if (!new)
		{
			ft_dblst_clear(&lst, free);
			return (NULL);
		}
		ft_dblst_addback(&lst, new);
		++ar;
	}
	return (lst);
}
