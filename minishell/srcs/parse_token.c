/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:13:37 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/24 15:06:14 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	parse_squote(const char **str, char **plain)
{
	const char	*p;

	*str = *str + 1;
	p = ft_strchr(*str, '\'');
	if (!p)
		return (1);
	*plain = str_join_free(*plain, ft_substr(*str, 0, p - *str));
	*str = p + 1;
	return (0);
}

static int	parse_dol(const char **str, char **plain, t_env *env)
{
	const char	*p;
	char		*name;
	char		*val;

	*str = *str + 1;
	p = *str;
	if (*p != '\0' && *p != ' ' && *p != '"' && *p != '\'')
	{
		if (*p != '$')
			while (*p && !isspechar(*p) && !ft_isspace(*p)
				&& (ft_isalnum(*p) || *p == '?' || *p == '_'))
				++p;
		else
			++p;
		name = ft_substr(*str, 0, p - *str);
		val = env_get_value(env, name);
		*plain = str_join_free(*plain, val);
		free(name);
	}
	else
		*plain = str_join_free(*plain, ft_strdup("$"));
	*str = p;
	return (0);
}

static int	parse_dquote(const char **str, char **plain, t_env *env)
{
	const char	*p;

	*str = *str + 1;
	p = *str;
	while (*p && *p != '"')
	{
		if (*p == '"' || *p == '$')
		{
			*plain = str_join_free(*plain, ft_substr(*str, 0, p - *str));
			if (*p == '\'')
				if (parse_squote(&p, plain))
					return (1);
			if (*p == '$')
				if (parse_dol(&p, plain, env))
					return (1);
			*str = p;
		}
		else
			++p;
	}
	if (!*p)
		return (1);
	*plain = str_join_free(*plain, ft_substr(*str, 0, p - *str));
	*str = p + 1;
	return (0);
}

static int	subparse(const char **p, char **plain, t_env *env)
{
	int	er;

	er = 0;
	if (**p == '"')
		er = parse_dquote(p, plain, env);
	else if (**p == '\'')
		er = parse_squote(p, plain);
	else if (**p == '$')
		er = parse_dol(p, plain, env);
	if (er)
	{
		printf("minishell: parsing error, missing quote near '%c'\n", **p);
		free(*plain);
	}
	return (er);
}

int	parse_token(const char **str, char **token, t_env *env)
{
	const char	*p;
	int			i;
	char		*plain;

	plain = NULL;
	p = *str;
	i = 0;
	while (*p && !ft_isspace(*p) && !isinstchar(*p))
	{
		if (isspechar(*p))
		{
			plain = str_join_free(plain, ft_substr(*str, 0, p - *str));
			if (subparse(&p, &plain, env))
				return (1);
			*str = p;
		}
		else
			++p;
		i++;
	}
	*token = str_join_free(plain, ft_substr(*str, 0, p - *str));
	*str = p;
	return (0);
}
