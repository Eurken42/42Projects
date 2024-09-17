/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:30:27 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/16 14:01:08 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_pwd(t_shell *shell, char **args, char **env)
{
	char	*homedir;

	(void) env;
	if (ft_strlen_2pts(args) != 1)
		return (ft_error(shell, 1, 1, "pwd: too many arguments\n"));
	else
	{
		homedir = env_get_value(shell->env, "PWD");
		if (!homedir)
			return (ft_error(shell, 1, 1,
					"minishell: command not found: pwd\n"));
		else
		{
			printf("%s\n", homedir);
			free(homedir);
		}
	}
	return (0);
}
