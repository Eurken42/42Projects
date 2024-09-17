/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:56:13 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/25 19:02:28 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	setup_pipe(int in, int pipe[2])
{
	int	out;

	if (in != STDIN)
	{
		close(STDIN);
		dup2(in, STDIN);
		close(in);
	}
	close(pipe[0]);
	out = pipe[1];
	if (out != STDOUT)
	{
		close(STDOUT);
		dup2(out, STDOUT);
		close(out);
	}
}

static pid_t	fork_pipe(int in, int pipe[2], t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
	{
		dprintf(2, "fork error\n");
		return (-1);
	}
	else if (pid == 0)
	{
		reset_signal(0);
		setup_pipe(in, pipe);
		ret = exec_cmd(cmd, shell);
		close(STDIN);
		close(STDOUT);
		exit(ret);
	}
	else
		reset_signal(2);
	if (in != STDIN)
		close(in);
	if (pipe[1] != STDOUT)
		close(pipe[1]);
	return (pid);
}

static void	wait_pipes(pid_t *pids, t_shell *shell)
{
	char	*ret;
	int		status;

	while (pids && *pids > 1)
		waitpid(*(pids++), &status, 0);
	if (WIFEXITED(status))
	{
		ret = ft_itoa(WEXITSTATUS(status));
		env_set_value(shell->env, "?", ret);
		free(ret);
	}
}

void	exec_pipes(t_dblst *cmds, t_shell *shell)
{
	pid_t	*pids;
	pid_t	*pid;
	int		fd[2];
	int		in;

	pids = ft_calloc(ft_dblst_size(cmds) + 1, sizeof(*pids));
	pid = pids;
	in = STDIN;
	while (pids && cmds)
	{
		if (cmds->next)
			pipe(fd);
		else
		{
			close(fd[1]);
			fd[1] = STDOUT;
		}
		*pid = fork_pipe(in, fd, (t_cmd *)cmds->content, shell);
		++pid;
		in = fd[0];
		cmds = cmds->next;
	}
	close(fd[0]);
	wait_pipes(pids, shell);
	free(pids);
}
