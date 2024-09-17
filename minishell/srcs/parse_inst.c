/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:26:44 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/14 16:10:51 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static t_dblst	*add_cmd_to_pipe(t_inst	**inst, t_dblst *tokens, t_dblst **t)
{
	t_cmd	*cmd;

	if (!tokens->prev)
	{
		printf("minishell: parse error near '%s'\n", tokens->content);
		inst_destroy(inst);
		return (NULL);
	}
	if (!*inst)
		*inst = inst_pipe_create();
	tokens->prev->next = NULL;
	tokens->prev = NULL;
	cmd = cmd_from_tokens(t);
	if (!cmd)
		return (NULL);
	inst_add_cmd(*inst, cmd);
	if (!tokens->next)
	{
		printf("minishell: parse error near '%s'\n", tokens->content);
		ft_dblst_delone(tokens, free);
		inst_destroy(inst);
		return (NULL);
	}
	return (tokens);
}

static int	parse_pipe(t_dblst **tokens, t_inst **inst)
{
	t_dblst	*t;

	*inst = NULL;
	t = *tokens;
	while (*tokens)
	{
		if (ft_strncmp((*tokens)->content, "|", 2) == 0)
		{
			*tokens = add_cmd_to_pipe(inst, *tokens, &t);
			ft_dblst_clear(&t, free);
			if (!*inst)
				return (1);
			*tokens = (*tokens)->next;
			ft_dblst_delone((*tokens)->prev, free);
			(*tokens)->prev = NULL;
			t = *tokens;
		}
		else
			*tokens = (*tokens)->next;
	}
	if (*inst)
		inst_add_cmd(*inst, cmd_from_tokens(&t));
	*tokens = t;
	return (0);
}

t_inst	*inst_from_tokens(t_dblst **tokens)
{
	t_cmd	*cmd;
	t_inst	*inst;
	int		er;

	cmd = NULL;
	if (!tokens || !*tokens)
		return (NULL);
	er = parse_pipe(tokens, &inst);
	if (inst)
		return (inst);
	else if (!er)
		cmd = cmd_from_tokens(tokens);
	if (cmd && cmd->type == CMDT_ENV)
		return (inst_env_create(cmd));
	else if (cmd)
		return (inst_cmd_create(cmd));
	else
		return (NULL);
}
