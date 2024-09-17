/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:07:39 by gluisier          #+#    #+#             */
/*   Updated: 2021/12/03 21:02:54 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_bufi	t_bufi;
struct s_bufi
{
	char	buf[BUFFER_SIZE];
	int		i;
	ssize_t	r;
};

char	*get_next_line(int fd);

t_bufi	*create_bufi(int fd);
void	free_bufi(t_bufi **bufi);

size_t	gnl_strlen(char *str);
char	*gnl_substr(char *str, int start, int end);
char	*gnl_join_and_free(char *s1, char *s2);

#endif
