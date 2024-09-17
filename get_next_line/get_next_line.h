/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:15:17 by scorreia          #+#    #+#             */
/*   Updated: 2021/12/29 19:05:56 by scorreia         ###   ########.fr       */
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

char		*get_next_line(int fd);
char		*get_one_line(char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s1, char c);
char		*ft_strcpy(char *src, char *dst, char set, int *k);
int			len(const char *s, char set);

#endif
