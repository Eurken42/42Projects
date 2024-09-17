/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:15:17 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/20 13:15:58 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char		*get_next_line(int fd);
char		*get_one_line(char *s1);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr_gnl(const char *s1, char c);
char		*ft_strcpy(char *src, char *dst, char set, int *k);
int			len(const char *s, char set);

#endif
