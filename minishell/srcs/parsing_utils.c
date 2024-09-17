/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:18:14 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/14 15:48:24 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	isspechar(char c)
{
	return (c == '"' || c == '\'' || c == '$' || c == '>' || c == '<');
}

int	isinstchar(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	token_is_redirect(char *token)
{
	return (ft_strncmp(token, ">", 2) == 0
		|| ft_strncmp(token, ">>", 3) == 0
		|| ft_strncmp(token, "<", 2) == 0
		|| ft_strncmp(token, "<<", 3) == 0);
}

int	ft_strchrnb(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
			i++;
		++s;
	}
	return (i);
}
