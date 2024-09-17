/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:42:40 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/12 15:00:06 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	assign_env_var(t_env *env, t_dblst *new_vars)
{
	while (new_vars)
	{
		env_new_var(env, new_vars->content);
		new_vars = new_vars->next;
	}
}

int	is_special_car(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0 && str[i] != '=')
			return (1);
	return (0);
}

t_dblst	*env_lst_contains(t_dblst *lst, char *name)
{
	char	*cont;
	t_dblst	*node;

	node = NULL;
	while (!node && lst)
	{
		cont = lst->content;
		if (ft_strncmp(name, cont, ft_strlen(name)) == 0
			&& cont[ft_strlen(name)] == '=')
			node = lst;
		else
			lst = lst->next;
	}
	return (lst);
}

int	env_set_value(t_env *env, char *name, char *value)
{
	t_dblst	*node;
	char	*str;
	size_t	size;

	if (!env || !name)
		return (1);
	node = env_lst_contains(env->global, name);
	if (!node)
		node = env_lst_contains(env->local, name);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	str = ft_calloc(size, sizeof(*str));
	ft_strlcat(str, name, size);
	ft_strlcat(str, "=", size);
	ft_strlcat(str, value, size);
	if (!node)
		ft_dblst_addback(&env->local, ft_dblst_new(str));
	else
	{
		free(node->content);
		node->content = str;
	}
	return (0);
}

int	env_export_value(t_env *env, char *name, char *value)
{
	t_dblst	*nodel;
	t_dblst	*nodeg;
	char	*str;
	size_t	size;

	if (!env || !name)
		return (1);
	if (value == NULL)
		value = "";
	nodel = env_lst_contains(env->local, name);
	nodeg = env_lst_contains(env->global, name);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	str = ft_calloc(size, sizeof(*str));
	ft_strlcat(str, name, size);
	ft_strlcat(str, "=", size);
	ft_strlcat(str, value, size);
	if (nodeg == NULL)
		ft_dblst_addback(&env->global, ft_dblst_new(str));
	else if (nodel && nodeg)
	{
		free(nodeg->content);
		nodeg->content = str;
	}
	return (0);
}
