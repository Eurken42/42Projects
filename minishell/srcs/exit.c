/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:33:27 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/12 19:27:17 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	string_is_num(char *str)
{
	if (!str)
		return (0);
	while (*str && ft_isdigit(*str))
		++str;
	if (*str)
		return (0);
	return (1);
}

int	ft_exit(t_shell *shell, char **args, char **env)
{
	char	*ret;
	int		code;

	(void) env;
	if (args)
		if (ft_strlen_2pts(args) >= 3)
			return (ft_error(shell, 1, 1, "exit: too many arguments"));
	ret = env_get_value(shell->env, "?");
	shell_destroy(&shell);
	code = ft_atoi(ret);
	printf("exit\n");
	if (!args[1])
		exit(code);
	else if (string_is_num(args[1]))
		exit(ft_atoi(args[1]));
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	return (0);
}
