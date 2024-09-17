/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:29:59 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/29 01:44:55 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_bufi	*create_bufi(int fd)
{
	t_bufi	*bufi;

	if (fd < 0 || fd > 4095)
		return (NULL);
	bufi = malloc(sizeof(t_bufi));
	bufi->i = 0;
	bufi->r = read(fd, bufi->buf, BUFFER_SIZE);
	return (bufi);
}

void	free_bufi(t_bufi **bufi)
{
	if (bufi)
	{
		free(*bufi);
		*bufi = NULL;
	}
}

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*gnl_substr(char *str, int start, int end)
{
	char	*sub;
	int		i;

	if (!str || end <= start)
		return (NULL);
	sub = malloc(sizeof(char) * (end - start + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		sub[i] = str[start + i];
		++i;
	}
	sub[i] = 0;
	return (sub);
}

char	*gnl_join_and_free(char	*s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	join = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	free(s1);
	free(s2);
	return (join);
}
