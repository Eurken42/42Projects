/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:30:27 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/24 15:14:08 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static t_dblst	*env_from_tokens(t_dblst **tokens)
{
	t_dblst	*env;
	t_dblst	*tkn;
	char	*str;

	if (!tokens || !*tokens)
		return (NULL);
	env = NULL;
	tkn = *tokens;
	while (tkn && ft_strchr(tkn->content, '='))
	{
		str = ft_strdup(tkn->content);
		ft_dblst_addback(&env, ft_dblst_new(str));
		tkn = tkn->next;
	}
	if (tkn)
	{
		if (tkn->prev)
			tkn->prev->next = NULL;
		tkn->prev = NULL;
	}
	if (env)
		ft_dblst_clear(tokens, free);
	*tokens = tkn;
	return (env);
}

static t_dblst	*remove_redirect_tokens(t_dblst *red)
{
	t_dblst	*cur;
	t_dblst	*next;

	if (red->next)
		next = red->next->next;
	else
		next = NULL;
	if (red->prev)
		red->prev->next = next;
	if (next)
		next->prev = red->prev;
	cur = red;
	ft_dblst_delone(cur->next, free);
	ft_dblst_delone(cur, free);
	return (next);
}

static char	*cmd_init_redirect(t_cmd *cmd, t_dblst *tokens)
{
	char	*red;

	while (tokens)
	{
		if (token_is_redirect((char *)tokens->content))
		{
			if (!tokens->next || !tokens->prev
				|| token_is_redirect((char *)tokens->next->content))
				return (tokens->content);
			red = ft_strdup((char *)tokens->next->content);
			if (ft_strncmp(tokens->content, ">", 2) == 0
				|| ft_strncmp(tokens->content, ">>", 3) == 0)
				cmd->f_write = red;
			if (ft_strncmp(tokens->content, ">>", 3) == 0)
				cmd->w_mode = O_WRONLY | O_CREAT | O_APPEND;
			if (ft_strncmp(tokens->content, "<", 2) == 0)
				cmd->f_read = red;
			if (ft_strncmp(tokens->content, "<<", 3) == 0)
				cmd->heredoc = red;
			tokens = remove_redirect_tokens(tokens);
		}
		else
			tokens = tokens->next;
	}
	return (NULL);
}

t_cmd	*cmd_from_tokens(t_dblst **tokens)
{
	t_dblst			*tmp_env;
	t_cmd			*cmd;
	char			*e_token;
	unsigned int	i;

	if (!tokens || !*tokens)
		return (NULL);
	tmp_env = env_from_tokens(tokens);
	if (!*tokens)
		return (cmd_create_env(tmp_env));
	i = bi_get_index((*tokens)->content);
	if (i < BI_LAST)
		cmd = cmd_create_bi(i, tmp_env);
	else
		cmd = cmd_create_bo(ft_strdup((char *)(*tokens)->content), tmp_env);
	e_token = cmd_init_redirect(cmd, *tokens);
	if (e_token)
	{
		printf("minishell: parse error near '%s'\n", e_token);
		cmd_destroy(&cmd);
	}
	else
		cmd->args = ltoa(*tokens);
	return (cmd);
}
