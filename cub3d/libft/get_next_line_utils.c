/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:35:56 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/20 13:15:28 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*d;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	d = (char *) malloc((len(s1, '\0') + len(s2, '\0') + 1) * sizeof(char));
	if (!d)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
		d[k++] = s1[i++];
	i = 0;
	while (s2[i])
		d[k++] = s2[i++];
	d[k] = '\0';
	free(s1);
	return (d);
}

int	len(const char *s, char set)
{
	int	i;

	i = 0;
	while (s[i] != set)
		i++;
	if (set == '\0')
		i++;
	else
		i += 2;
	return (i);
}

char	*ft_strchr_gnl(const char *s, char c)
{
	char	*b;
	int		i;

	i = 0;
	b = (char *)s;
	while (b[i])
	{
		if (b[i] == c)
			return (b + i);
		i++;
	}
	return (NULL);
}

char	*ft_strcpy(char *src, char *dst, char set, int *k)
{
	int	w;

	w = 0;
	while (src[*k] != set)
	{
		dst[w] = src[*k];
		w++;
		*k += 1;
	}
	if (set == '\n')
		dst[w++] = '\n';
	*k += 1;
	dst[w] = '\0';
	if (set == '\0')
	{
		free(src);
		src = NULL;
		*k = -1;
	}
	if (dst[0] == '\0')
	{
		free(dst);
		return (NULL);
	}
	return (dst);
}
