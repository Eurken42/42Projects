/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:04:23 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/12 19:29:41 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_free_next(t_dblst *node)
{
	free(node->content);
	node->content = NULL;
	free(node->next);
}

void	ft_free_node(t_dblst *node)
{
	free(node->content);
	node->content = NULL;
	free(node);
}

void	ft_del_node(t_dblst **nodeg)
{
	t_dblst	*node;

	node = *nodeg;
	if (node)
	{
		if (node->next == NULL)
		{
			node->prev->next = NULL;
			ft_free_node(node);
		}
		else if (node->prev != NULL)
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
			ft_free_node(node);
		}
		else
		{
			ft_free_next(node);
			node->content = node->next->content;
			node->next = node->next->next;
			node->next->next->prev = node;
		}
	}
}

t_dblst	*env_lst_contains_empty(t_dblst *lst, char *name)
{
	char	*cont;
	t_dblst	*node;

	node = NULL;
	while (!node && lst)
	{
		cont = lst->content;
		if (ft_strncmp(name, cont, ft_strlen(name)) == 0)
			node = lst;
		else
			lst = lst->next;
	}
	return (lst);
}

int	ft_unset(t_shell *shell, char **args, char **env)
{
	int		i;
	t_dblst	*node;

	(void) env;
	if (!args || !*args)
		return (ft_error(shell, 1, 1, "unset: not enough arguments\n"));
	if (!shell)
		return (-1);
	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "_"))
		{
			node = env_lst_contains(shell->env->global, args[i]);
			ft_del_node(&node);
			if (!node)
			{
				node = env_lst_contains_empty(shell->env->global, args[i]);
				ft_del_node(&node);
			}
			node = env_lst_contains(shell->env->local, args[i]);
			ft_del_node(&node);
		}
	}
	return (0);
}
