/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:03:30 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/12 19:28:46 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_write_env(char **enva, int i)
{
	int	j;
	int	k;

	k = 0;
	j = -1;
	printf("declare -x ");
	while (enva[i][++j])
	{
		if (enva[i][j] != '=')
			printf("%c", enva[i][j]);
		else
		{
			printf("%c", enva[i][j]);
			printf("\"");
			k = 1;
		}
	}
	if (k)
		printf("\"");
	printf("\n");
}

int	ft_env_ord(t_env *env)
{
	char	**enva;
	int		i;

	i = -1;
	if (!env)
		return (-1);
	enva = ltoa(env->global);
	bubble_sort(enva);
	while (enva[++i])
		if (ft_strncmp(enva[i], "_=", 2))
			ft_write_env(enva, i);
	free_array(enva);
	free(enva);
	return (0);
}

void	ft_export_value(t_shell *shell, char **val, char *value)
{
	if (val[1])
		env_set_value(shell->env, val[0], val[1]);
	else
		env_export_value(shell->env, val[0], value);
}

int	env_export_empty(t_env *env, char *name)
{
	t_dblst	*nodel;
	t_dblst	*nodeg;
	char	*str;
	size_t	size;

	if (!env || !name)
		return (1);
	nodel = env_lst_contains(env->local, name);
	nodeg = env_lst_contains(env->global, name);
	size = ft_strlen(name) + 1;
	str = ft_calloc(size, sizeof(*str));
	ft_strlcat(str, name, size);
	if (nodeg == NULL)
		ft_dblst_addback(&env->global, ft_dblst_new(str));
	else if (nodel && nodeg)
	{
		free(nodeg->content);
		nodeg->content = str;
	}
	return (0);
}

int	ft_export(t_shell *shell, char **args, char **env)
{
	char	*value;
	char	**val;
	int		i;

	(void) env;
	i = 0;
	if (ft_strlen_2pts(args) == 1)
		return (ft_env_ord(shell->env));
	if (!shell->env)
		return (-1);
	while (args[++i])
	{
		val = ft_split(args[i], '=');
		value = env_get_value(shell->env, val[0]);
		if (value != NULL)
			ft_export_value(shell, val, value);
		else if (ft_strchr(args[i], '=') != NULL)
			env_export_value(shell->env, val[0], val[1]);
		else
			env_export_empty(shell->env, args[i]);
		free(value);
		free_array(val);
		free(val);
	}
	return (0);
}
