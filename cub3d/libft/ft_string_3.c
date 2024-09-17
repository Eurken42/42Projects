/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:18:12 by scorreia          #+#    #+#             */
/*   Updated: 2022/12/20 16:38:19 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_strlen_charset(const char *s, char set)
{
	int	i;

	i = 0;
	while (s[i] != set)
		i++;
	return (i);
}

char	*ft_strdup_set(const char *str, char set)
{
	size_t	len;
	char	*s;

	len = ft_strlen_charset(str, set);
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str, len + 1);
	return (s);
}

int	ft_strncmp_s(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n - 1 && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
		--n;
	}
	while (s1[i])
		++i;
	if (i != 1)
		return (-1);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strdup_nl(const char *str, int size)
{
	char	*s;
	int		i;

	if (!str)
		return (NULL);
	s = ft_calloc(size + 1, sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		s[i] = str[i];
		i++;
	}
	if (i == 0)
	{
		free(s);
		return (NULL);
	}
	s[i] = '\0';
	return (s);
}

void	free_array(char **ar)
{
	if (!ar)
		return ;
	while (*ar)
	{
		free(*ar);
		++ar;
	}
}
