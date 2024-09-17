/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:26:10 by scorreia          #+#    #+#             */
/*   Updated: 2022/10/25 18:45:18 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <stdio.h>

void	catch_ctrl(int signum, t_shell *shell)
{
	struct termios	t;

	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGCTRLD)
	{
		printf("exit\n");
		shell_destroy(&shell);
		exit(0);
	}
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

int	get_last_space(char *str)
{
	int	i;
	int	is_char;

	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (str[i] >= 33 && str[i] <= 126)
				is_char = 1;
		if ((str[i] == ' ' || str[i] == '|') && is_char == 1)
			return (i + 1);
	}
	return (0);
}

void	update_underscore(t_env *env, char *line)
{
	char	*last_args;

	add_history(line);
	last_args = line + get_last_space(line);
	if (ft_strncmp(last_args, "$_", 2))
	{
		env_set_value(env, "_", last_args);
		if (last_args[0] == '$' && ft_strlen(last_args) > 1)
		{
			last_args = env_get_value(env, last_args + 1);
			if (last_args)
			{
				env_set_value(env, "_", last_args);
				free(last_args);
			}
			else
			{
				line[get_last_space(line)] = '\0';
				update_underscore(env, line);
			}
		}
	}
}

void	init_signal_env(t_shell *shell)
{
	int		shell_lvl;
	char	*shell_level;
	char	*get_pid;
	char	*lvl;
	char	*shell_link;

	signal_handler(-1, shell);
	reset_signal(1);
	lvl = env_get_value(shell->env, "SHLVL");
	shell_link = env_get_value(shell->env, "_");
	shell_lvl = ft_atoi(lvl) + 1;
	get_pid = ft_itoa(getpid());
	shell_level = ft_itoa(shell_lvl);
	env_set_value(shell->env, "?", "0");
	env_set_value(shell->env, "$", get_pid);
	env_set_value(shell->env, "SHELL", shell_link);
	env_set_value(shell->env, "SHLVL", shell_level);
	free(lvl);
	free(get_pid);
	free(shell_link);
	free(shell_level);
}

void	reset_signal(int option)
{
	if (option == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (option == 1)
	{
		signal(SIGINT, (void (*)(int))signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
