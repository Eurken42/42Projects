/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:13:03 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/29 01:44:52 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

ssize_t	update_buffer(int fd, t_bufi *bufi)
{
	bufi->r = read(fd, bufi->buf, BUFFER_SIZE);
	bufi->i = 0;
	return (bufi->r);
}

char	*get_next_buf_line(t_bufi *bufi)
{
	int	start;

	if (bufi->i < 0 || bufi->i >= bufi->r)
		return (NULL);
	else
	{
		start = bufi->i;
		while (bufi->i < bufi->r && bufi->buf[bufi->i] != '\n')
			++bufi->i;
		if (bufi->i < bufi->r)
			return (gnl_substr(bufi->buf, start, ++bufi->i));
		else if (bufi->r < BUFFER_SIZE)
			return (gnl_substr(bufi->buf, start, bufi->i++));
	}
	bufi->i = start;
	return (NULL);
}

char	*gnl_build_line(int fd, t_bufi *bufi, char *line)
{
	char	*part;

	part = gnl_substr(bufi->buf, bufi->i, bufi->r);
	while (!line)
	{
		update_buffer(fd, bufi);
		if (bufi->r < 0 || (bufi->r == 0 && !part))
		{
			free_bufi(&bufi);
			return (NULL);
		}
		if (bufi->r == 0)
			return (part);
		line = get_next_buf_line(bufi);
		if (line)
			line = gnl_join_and_free(part, line);
		else if (bufi->r < BUFFER_SIZE)
			line = gnl_join_and_free(part,
					gnl_substr(bufi->buf, bufi->i, bufi->r));
		else
			part = gnl_join_and_free(part,
					gnl_substr(bufi->buf, bufi->i, BUFFER_SIZE));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_bufi	*bufi = NULL;

	if (!bufi)
		bufi = create_bufi(fd);
	if (!bufi || bufi->r <= 0)
	{
		free_bufi(&bufi);
		return (NULL);
	}
	line = get_next_buf_line(bufi);
	if (!line)
		line = gnl_build_line(fd, bufi, line);
	return (line);
}
