/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:55:57 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/24 15:12:41 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static const char	*parse_inst_token(const char *line, char **token)
{
	char	c;

	c = *line;
	if (*(line + 1) == *line)
		*token = ft_substr(line, 0, 2);
	else
		*token = ft_substr(line, 0, 1);
	return (line + ft_strlen(*token));
}

static t_dblst	*line_to_tokens(const char *line, t_env *env)
{
	int		er;
	char	*tkn;
	t_dblst	*tokens;

	tokens = NULL;
	while (ft_isspace(*line))
		++line;
	while (*line)
	{
		er = 0;
		if (isinstchar(*line))
			line = parse_inst_token(line, &tkn);
		else
			er = parse_token(&line, &tkn, env);
		if (!tkn || er)
		{
			ft_dblst_clear(&tokens, free);
			return (NULL);
		}
		ft_dblst_addback(&tokens, ft_dblst_new(tkn));
		while (ft_isspace(*line))
			++line;
	}
	return (tokens);
}

t_inst	*parse_line(const char *line, t_env *env)
{
	t_dblst	*tokens;
	t_inst	*inst;
	char	*er;

	inst = NULL;
	tokens = line_to_tokens(line, env);
	if (tokens)
		inst = inst_from_tokens(&tokens);
	ft_dblst_clear(&tokens, free);
	if (!inst)
	{
		er = ft_itoa(278);
		env_set_value(env, "?", er);
		free(er);
	}
	return (inst);
}
