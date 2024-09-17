/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:40:39 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/14 16:47:59 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static t_cmd	*cmd_create(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->w_mode = O_WRONLY | O_CREAT | O_TRUNC;
	return (cmd);
}

t_cmd	*cmd_create_env(t_dblst *tmp_env)
{
	t_cmd	*cmd;

	cmd = cmd_create();
	cmd->type = CMDT_ENV;
	cmd->tmp_env = tmp_env;
	return (cmd);
}

t_cmd	*cmd_create_bi(enum e_bi name, t_dblst *tmp_env)
{
	t_cmd	*cmd;

	cmd = cmd_create();
	if (!cmd || name >= BI_LAST)
		return (NULL);
	cmd->name.index = name;
	cmd->type = CMDT_BI;
	cmd->tmp_env = tmp_env;
	return (cmd);
}

t_cmd	*cmd_create_bo(char *path, t_dblst *tmp_env)
{
	t_cmd	*cmd;

	cmd = cmd_create();
	if (!cmd)
		return (NULL);
	cmd->name.path = path;
	cmd->tmp_env = tmp_env;
	cmd->type = CMDT_BO;
	return (cmd);
}

void	cmd_destroy(t_cmd **cmd)
{
	t_cmd	*c;

	if (!cmd || !*cmd)
		return ;
	c = *cmd;
	if (c->type == CMDT_BO)
		free(c->name.path);
	free_array(c->args);
	free(c->args);
	ft_dblst_clear(&c->tmp_env, free);
	free(c->f_read);
	free(c->f_write);
	free(c->heredoc);
	free(c);
	*cmd = NULL;
}
