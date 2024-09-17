/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:17:40 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/16 13:41:23 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_env	*env_create(char **envp)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	if (!env)
		return (NULL);
	env->global = ft_atol(envp);
	env->local = NULL;
	if (!env->global)
	{
		free(env);
		return (NULL);
	}
	return (env);
}

void	env_destroy(t_env **env)
{
	t_env	*e;

	if (!env || !*env)
		return ;
	e = *env;
	ft_dblst_clear(&e->global, free);
	ft_dblst_clear(&e->local, free);
	free(e);
	*env = NULL;
}

int	env_new_var(t_env *env, char *str)
{
	char	*p;
	char	*name;
	char	*val;

	p = ft_strchr(str, '=');
	if (!p)
		return (0);
	name = ft_substr(str, 0, p - str);
	val = ft_strdup(p + 1);
	env_set_value(env, name, val);
	free(name);
	free(val);
	return (1);
}

char	*env_get_value(t_env *env, char *name)
{
	char	*cont;
	t_dblst	*node;

	if (!env || !name)
		return (NULL);
	node = env_lst_contains(env->global, name);
	if (!node)
		node = env_lst_contains(env->local, name);
	if (!node)
		return (NULL);
	cont = node->content;
	return (ft_strdup(cont + ft_strlen_charset(cont, '=') + 1));
}

int	ft_env(t_shell *shell, char **args, char **env)
{
	int		i;

	i = -1;
	(void) args;
	if (!shell->env)
		return (-1);
	env_set_value(shell->env, "_", "env");
	while (env[++i])
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
	return (0);
}
