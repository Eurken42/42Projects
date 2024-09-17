/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:04:05 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/12 16:48:51 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_inst	*inst_pipe_create(void)
{
	t_inst	*inst;

	inst = ft_calloc(1, sizeof(*inst));
	if (!inst)
		return (NULL);
	inst->type = INST_PIPE;
	return (inst);
}

t_inst	*inst_cmd_create(t_cmd *cmd)
{
	t_inst	*inst;

	inst = ft_calloc(1, sizeof(*inst));
	if (!inst)
		return (NULL);
	inst->type = INST_CMD;
	inst->data.cmd = cmd;
	return (inst);
}

t_inst	*inst_env_create(t_cmd *cmd)
{
	t_inst	*inst;

	inst = ft_calloc(1, sizeof(*inst));
	if (!inst)
		return (NULL);
	inst->type = INST_ENV;
	inst->data.cmd = cmd;
	return (inst);
}

void	inst_destroy(t_inst **inst)
{
	t_inst	*i;
	t_dblst	*cmd;

	if (!inst || !*inst)
		return ;
	i = *inst;
	if (i->type == INST_ENV || i->type == INST_CMD)
		cmd_destroy(&i->data.cmd);
	else if (i->type == INST_PIPE)
	{
		cmd = i->data.cmds;
		while (cmd)
		{
			cmd_destroy((t_cmd **)&cmd->content);
			cmd = cmd->next;
		}
		ft_dblst_clear(&(i->data.cmds), free);
	}
	free(i);
	*inst = NULL;
}

void	inst_add_cmd(t_inst *inst, t_cmd *cmd)
{
	if (!inst || !cmd || inst->type != INST_PIPE)
		return ;
	ft_dblst_addback(&inst->data.cmds, ft_dblst_new(cmd));
}
