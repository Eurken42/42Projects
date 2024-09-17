/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:06:13 by scorreia          #+#    #+#             */
/*   Updated: 2022/09/21 13:36:18 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdarg.h>
#include <stdlib.h>

int	ft_strlen_2pts(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(void *str1, void *str2)
{
	int		i;
	char	*s1;
	char	*s2;

	s1 = str1;
	s2 = str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		++i;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp_mishell(const char *s1, const char *s2, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;
	size_t			i;

	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (-1);
	while (b1[i] == b2[i] && b1[i] && b2[i])
		i++;
	if (i == ft_strlen(s1) && b2[i] == '\0')
		return (0);
	return (-1);
}

int	ft_error(t_shell *shell, int code, int count, ...)
{
	va_list	other_err;
	char	*num;

	num = ft_itoa(code);
	env_set_value(shell->env, "?", num);
	free(num);
	va_start(other_err, count);
	while (--count >= 0)
		ft_putendl_fd(va_arg(other_err, char *), STDERR);
	va_end(other_err);
	return (code);
}

char	*ft_strjoin_var(int count, ...)
{
	va_list	str;
	char	*join;
	char	*buf;
	char	*cpy;
	int		i;

	i = -1;
	va_start(str, count);
	join = NULL;
	while (++i < count)
	{
		buf = va_arg(str, char *);
		if (join == NULL)
			join = ft_strdup(buf);
		else
		{
			cpy = ft_strdup(join);
			free(join);
			join = ft_strjoin(cpy, buf);
			free(cpy);
		}
	}
	va_end(str);
	return (join);
}
