/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:14:35 by scorreia          #+#    #+#             */
/*   Updated: 2021/12/29 19:22:23 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char static	*save;
	char		*buf;
	int			is_reading;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	is_reading = 1;
	while (is_reading > 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		is_reading = read(fd, buf, BUFFER_SIZE);
		buf[is_reading] = '\0';
		if (is_reading > 0)
			save = ft_strjoin(save, buf);
		free(buf);
		if ((save == NULL && is_reading <= 0) || is_reading == -1)
			return (NULL);
	}
	return (get_one_line(save));
}

char	*get_one_line(char *s1)
{
	static int	i;
	char		*s2;
	char		set;

	if (i == -1)
		return (NULL);
	if (ft_strchr(s1 + i, '\n') == NULL)
		set = '\0';
	else
		set = '\n';
	s2 = (char *) malloc(len(s1 + i, set) * sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	s2 = ft_strcpy(s1, s2, set, &i);
	return (s2);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd2;

	fd2 = open("tests/test2.txt", O_RDONLY);
	i = 1;
	while (i <= 2)
	{
		line = get_next_line(fd2);
		if (line == NULL)
			printf("\nline [%02d]: %s", i, line);
		else
			printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd2);
	return (0);
}*/
