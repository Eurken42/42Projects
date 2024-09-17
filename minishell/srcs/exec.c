/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:45:05 by scorreia          #+#    #+#             */
/*   Updated: 2022/10/25 18:45:27 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	exec_cmd_bo(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**env;

	if (!cmd || !shell)
		return ;
	if (cmd->type == CMDT_BO)
	{
		path = cmd_exist(cmd, shell->env);
		env = ltoa(cmd->tmp_env);
		execve(path, cmd->args, env);
		printf("minishell: Command not found: %s\n", cmd->name.path);
		if (path != cmd->name.path)
			free(path);
		free_array(env);
	}
	exit(127);
}

static void	setup_exec_cmd(t_cmd *cmd, t_shell *shell, int *fd)
{
	t_dblst	*env;

	fd[0] = dup(STDIN);
	fd[1] = dup(STDOUT);
	set_redirect_streams(cmd);
	env = shell->env->global;
	while (env)
	{
		ft_dblst_addback(&cmd->tmp_env, ft_dblst_new(ft_strdup(env->content)));
		env = env->next;
	}
}

int	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	int		fd[2];
	int		ret;
	char	**enva;

	ret = 127;
	if (cmd->type == CMDT_ENV)
	{
		assign_env_var(shell->env, cmd->tmp_env);
		return (0);
	}
	reset_signal(0);
	setup_exec_cmd(cmd, shell, fd);
	if (cmd->type == CMDT_BO)
		exec_cmd_bo(cmd, shell);
	else
	{
		enva = ltoa(cmd->tmp_env);
		ret = g_bi[cmd->name.index](shell, cmd->args, enva);
		free_array(enva);
		free(enva);
	}
	dup2(fd[0], STDIN);
	dup2(fd[1], STDOUT);
	return (ret);
}

void	sigint_heredoc(int signum)
{
	if (signum == SIGINT)
		exit(130);
}

void	fork_cmd(t_cmd *cmd, t_shell *shell)
{
	int		pid;
	int		status;
	char	*ret;

	if (!cmd || !shell)
		return ;
	if (cmd->type == CMDT_BO)
	{
		pid = fork();
		if (pid == 0)
			exec_cmd(cmd, shell);
		else
		{
			reset_signal(2);
			waitpid(pid, &status, 0);
		}
		if (WIFEXITED(status))
			ret = ft_itoa(WEXITSTATUS(status));
		else
			ret = ft_itoa(127);
	}
	else
		ret = ft_itoa(exec_cmd(cmd, shell));
	env_set_value(shell->env, "?", ret);
	free(ret);
}
