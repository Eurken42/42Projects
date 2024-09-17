/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:58:47 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/12 19:31:32 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <stdarg.h>

int	ft_strlen_charset(const char *s, char set)
{
	int	i;

	i = 0;
	while (s[i] != set)
		i++;
	return (i);
}

size_t	bi_get_index(char *name)
{
	const char	*names[BI_LAST] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit"};
	size_t		i;

	i = 0;
	while (i < BI_LAST)
	{
		if (ft_strncmp(name, names[i], ft_strlen(name) + 1) == 0)
			return (i);
		++i;
	}
	return (BI_UNKNOWN);
}

void	cmd_print(t_cmd *cmd)
{
	char	**arg;

	if (cmd->type == CMDT_BO)
		printf("cmd BO: %s\n", cmd->name.path);
	else
		printf("cmd BI: %d\n", cmd->name.index);
	arg = cmd->args;
	printf("  args: ");
	while (*arg)
	{
		printf("%s", *arg);
		printf(", ");
		++arg;
	}
	printf("null\n");
	printf("  f_read: %s\n", cmd->f_read);
	printf("  f_write: %s\n", cmd->f_write);
	printf("  w_mode: %d\n", cmd->w_mode);
	printf("  heredoc: %s\n", cmd->heredoc);
}

void	pipe_print(t_dblst *cmds)
{
	t_dblst	*c;

	c = cmds;
	printf("pipe: ");
	while (c)
	{
		printf("%s", ((t_cmd *)c->content)->args[0]);
		if (c->next)
			printf(" -> ");
		c = c->next;
	}
	printf("\n");
	while (cmds)
	{
		cmd_print((t_cmd *)cmds->content);
		cmds = cmds->next;
	}
}

char	**bubble_sort(char **src)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;

	n = 0;
	i = -1;
	while (src[n])
		n++;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - 1 - i)
		{
			if (ft_strcmp(src[j], src[j + 1]) > 0)
			{
				tmp = src[j];
				src[j] = src[j + 1];
				src[j + 1] = tmp;
			}
		}
	}
	return (src);
}
