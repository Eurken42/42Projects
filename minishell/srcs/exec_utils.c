/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:48:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/10/20 13:30:25 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char	*cmd_exist(t_cmd *cmd, t_env *env)
{
	struct stat	buffer;
	char		**path_exec;
	char		*file;
	int			exist;
	int			i;

	i = -1;
	path_exec = ft_split(env_get_value(env, "PATH"), ':');
	while (path_exec && path_exec[++i])
	{
		file = ft_strjoin_var(3, path_exec[i], "/", cmd->name.path);
		exist = stat(file, &buffer);
		if (exist == 0)
		{
			free_array(path_exec);
			return (file);
		}
		free(file);
		file = NULL;
	}
	free_array(path_exec);
	free(path_exec);
	return (cmd->name.path);
}

char	**get_cmd_env(t_cmd *cmd, t_shell *shell)
{
	t_dblst	*g;

	g = shell->env->global;
	while (g)
	{
		ft_dblst_addback(&cmd->tmp_env,
			ft_dblst_new(ft_strdup((char *)g->content)));
		g = g->next;
	}
	return (ltoa(cmd->tmp_env));
}

static void	setup_heredoc(const char *hd)
{
	int		fd;
	char	*line;

	fd = open(F_HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, &sigint_heredoc);
	signal(SIGQUIT, &sigint_heredoc);
	line = get_next_line(STDIN);
	while (ft_strncmp(line, hd, ft_strlen(hd) - 1))
	{
		write(fd, line, ft_strlen(line));
		line = get_next_line(STDIN);
	}
	close(fd);
}

void	set_redirect_streams(t_cmd *cmd)
{
	int	fd;

	if (cmd->heredoc)
	{
		setup_heredoc(cmd->heredoc);
		cmd->f_read = ft_strdup(F_HEREDOC);
	}
	if (cmd->f_read)
	{
		fd = open(cmd->f_read, O_RDONLY);
		if (fd < 0)
		{
			printf("minishell: %s: No such file or directory\n", cmd->f_read);
			exit(1);
		}
		dup2(fd, STDIN);
		close(fd);
	}
	if (cmd->f_write)
	{
		fd = open(cmd->f_write, cmd->w_mode, 0644);
		dup2(fd, STDOUT);
		close(fd);
	}
}
