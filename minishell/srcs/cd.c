/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:27:35 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/16 14:01:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*new_path(t_shell *shell, char *path, char **args)
{
	if (ft_strlen_2pts(args) == 1)
		path = env_get_value(shell->env, "HOME");
	else if (!ft_strncmp_mishell(args[1], "~", 1)
		|| !ft_strncmp_mishell(args[1], "--", 2))
		path = env_get_value(shell->env, "HOME");
	else if (!ft_strncmp_mishell(args[1], "-", 1))
	{
		path = env_get_value(shell->env, "OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	else
	{
		if (args[1][0] == '~')
			path = ft_strjoin(env_get_value(shell->env, "HOME"), args[1] + 1);
		else
			path = ft_strdup(args[1]);
	}
	return (path);
}

static int	cd_permission(char *path)
{
	int	ret;

	ret = access(path, R_OK);
	if (ret != 0)
	{
		ret = access(path, F_OK);
		if (ret == 0)
		{
			free(path);
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_shell *shell, char **args, char **env)
{
	char	tmp_pwd[PATH_MAX];
	char	*path;
	int		ret;

	(void) env;
	path = NULL;
	if (getcwd(tmp_pwd, sizeof(tmp_pwd)) == NULL)
		return (ft_error(shell, 1, 1, "cd: error during execution\n"));
	if (ft_strlen_2pts(args) >= 3)
		return (ft_error(shell, 1, 1, "cd: too many arguments\n"));
	path = new_path(shell, path, args);
	if (cd_permission(path))
		return (ft_error(shell, 1, 3, "cd: permission denied: ", args[1], "\n"));
	ret = chdir(path);
	if (path)
		free(path);
	if (ret != 0)
		return (ft_error(shell, 1, 3, "cd: not a directory: ", args[1], "\n"));
	env_set_value(shell->env, "OLDPWD", tmp_pwd);
	if (getcwd(tmp_pwd, sizeof(tmp_pwd)) == NULL)
		return (ft_error(shell, 1, 1, "cd: error during execution\n"));
	env_set_value(shell->env, "PWD", tmp_pwd);
	return (0);
}
