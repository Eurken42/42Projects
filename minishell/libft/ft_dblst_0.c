/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblst_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:13 by gluisier          #+#    #+#             */
/*   Updated: 2022/08/25 11:42:20 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblst	*ft_dblst_new(void *content)
{
	t_dblst	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	return (new);
}

void	ft_dblst_addfront(t_dblst **alst, t_dblst *new)
{
	t_dblst	*first;

	if (!alst || !new)
		return ;
	new->next = NULL;
	new->prev = NULL;
	first = *alst;
	if (first)
	{
		first->prev = new;
		new->next = first;
	}
	*alst = new;
}

void	ft_dblst_addback(t_dblst **alst, t_dblst *new)
{
	t_dblst	*last;

	if (!alst || !new)
		return ;
	new->next = NULL;
	new->prev = NULL;
	last = ft_dblst_last(*alst);
	if (!last)
		*alst = new;
	else
	{
		new->prev = last;
		last->next = new;
	}
}

int	ft_dblst_size(t_dblst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}

t_dblst	*ft_dblst_last(t_dblst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
