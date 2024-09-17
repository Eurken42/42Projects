/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblst_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:30:04 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/23 23:14:22 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_dblst	*ft_dblst_contains(t_dblst *lst, void *cont, int (*cmp)(void *, void *))
{
	while (lst && !cmp(cont, lst->content))
		lst = lst->next;
	return (lst);
}

void	ft_dblst_delone(t_dblst *lst, void (*del)(void *))
{
	if (lst)
	{
		(*del)(lst->content);
		lst->content = NULL;
		lst->next = NULL;
		lst->prev = NULL;
	}
	free(lst);
}

void	ft_dblst_clear(t_dblst **lst, void (*del)(void *))
{
	t_dblst	*p;
	t_dblst	*n;

	if (!lst || !*lst)
		return ;
	p = *lst;
	while (p->next)
	{
		n = p->next;
		ft_dblst_delone(p, del);
		p = n;
	}
	ft_dblst_delone(p, del);
	*lst = NULL;
}

void	ft_dblst_append(t_dblst **lst, t_dblst *ap)
{
	t_dblst	*last;

	if (!lst || !ap)
		return ;
	last = ft_dblst_last(*lst);
	if (!last)
		*lst = ap;
	else
	{
		ap->prev = last;
		last->next = ap;
	}
}
