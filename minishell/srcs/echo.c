/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:31:46 by scorreia          #+#    #+#             */
/*   Updated: 2022/10/25 19:41:24 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	check_final_nl(char **av, int i, int j, int option)
{
	if (!av[i + 1] && !av[i][j + 1] && av[i][j] == '\n' && option == 2)
		return (1);
	return (0);
}

void	ft_echo_write(char **args, int i, int option, t_shell *shell)
{
	int		j;
	char	*value;

	j = -1;
	value = env_get_value(shell->env, "HOME");
	if (!ft_strncmp(args[i], "~", 1) && ft_strncmp(args[i], "~~", 2)
		&& args[i][1] != '$')
		printf("%s%s", value, args[i] + 1);
	else
		while (args[i][++j] && check_final_nl(args, i, j, option) == 0)
			printf("%c", args[i][j]);
	if (args[i + 1])
		printf(" ");
	if (value)
		free(value);
}

int	ft_start_display(char **args, int i)
{
	int	j;

	j = 0;
	if (args[1][0] == '-')
	{
		while (args[++j])
		{
			i = 0;
			if (args[j][0] == '-')
			{
				while (args[j][++i])
					if (args[j][i] != 'n')
						return (j - 1);
				if (i == 1)
					return (j - 1);
			}
			else
				break ;
		}
		return (j - 1);
	}
	return (0);
}

int	ft_echo(t_shell *shell, char **args, char **env)
{
	int	i;
	int	nb;
	int	option;

	i = 0;
	(void) env;
	if (!args || !args[1])
	{
		printf("\n");
		return (0);
	}
	nb = ft_start_display(args, i);
	option = nb;
	while (args[++nb])
		ft_echo_write(args, nb, option, shell);
	if (option == 0)
		printf("\n");
	return (0);
}
