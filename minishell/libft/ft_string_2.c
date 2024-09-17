/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:23:46 by gluisier          #+#    #+#             */
/*   Updated: 2022/08/23 18:11:32 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_calloc(len + 1, sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	return (join);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]))
		--end;
	trim = ft_calloc(end - start + 2, sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1 + start, end - start + 2);
	return (trim);
}

static char	**ft_split_fill(char **split, const char *p, char c)
{
	const char	*n;
	size_t		i;

	i = 0;
	while (*p && *p == c)
		++p;
	while (*p)
	{
		n = ft_strchr(p, c);
		if (!n)
			n = ft_strchr(p, 0);
		split[i] = ft_substr(p, 0, n - p);
		if (!split[i])
		{
			while (i--)
				free(split[i]);
			free(split);
			return (NULL);
		}
		++i;
		while (*n && *n == c)
			++n;
		p = n;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	const char	*p;
	size_t		size;

	if (!s)
		return (NULL);
	size = 1;
	p = s + 1;
	while (*p)
	{
		if (*p == c && *(p - 1) != c && *(p + 1))
			++size;
		++p;
	}
	split = ft_calloc(size + 1, sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_split_fill(split, s, c));
}
