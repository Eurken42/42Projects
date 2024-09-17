/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:04:27 by gluisier          #+#    #+#             */
/*   Updated: 2021/12/17 15:05:58 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lst_contains(t_list *lst, void *cont, int (*cmp)(void *, void *))
{
	while (lst && !cmp(cont, lst->content))
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		(*del)(lst->content);
		lst->content = NULL;
		lst->next = NULL;
	}
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*n;

	if (!lst || !*lst)
		return ;
	p = *lst;
	while (p->next)
	{
		n = p->next;
		ft_lstdelone(p, del);
		p = n;
	}
	ft_lstdelone(p, del);
	*lst = NULL;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*cur;

	if (!lst)
		return (NULL);
	map = ft_lstnew((*f)(lst->content));
	if (!map)
		return (NULL);
	cur = map;
	while (lst->next)
	{
		lst = lst->next;
		cur->next = ft_lstnew((*f)(lst->content));
		if (!cur->next)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		cur = cur->next;
	}
	return (map);
}
