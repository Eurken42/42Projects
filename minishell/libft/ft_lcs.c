/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:49:18 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/23 22:23:43 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	**allocate_intar(size_t i, size_t j)
{
	int		**ar;
	size_t	x;

	ar = ft_calloc(i, sizeof(*ar));
	if (!ar)
		return (NULL);
	x = 0;
	while (x < i)
	{
		ar[x] = ft_calloc(j, sizeof(*(ar[x])));
		if (!ar[x])
		{
			free(ar[x]);
			while (x--)
				free(ar[x]);
			free(ar);
			return (NULL);
		}
		++x;
	}
	return (ar);
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	**ft_lcs_len(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	int		**c;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	c = allocate_intar(len1 + 1, len2 + 1);
	i = 0;
	while (c && i < len1)
	{
		j = 0;
		while (j < len2)
		{
			if (s1[i] == s2[j])
				c[i + 1][j + 1] = c[i][j] + 1;
			else
				c[i + 1][j + 1] = max(c[i + 1][j], c[i][j + 1]);
			++j;
		}
		++i;
	}
	return (c);
}

static char	*ft_lcs_backtrack(int **c, char *s1, int i, int j)
{
	char	*ret;
	char	*ap;
	char	*join;

	if (!i || !j)
		return (ft_strdup(""));
	if (c[i - 1][j] < c[i][j] && c[i - 1][j] == c[i][j - 1])
	{
		ret = ft_lcs_backtrack(c, s1, i - 1, j - 1);
		ap = ft_substr(s1, i - 1, 1);
		join = ft_strjoin(ret, ap);
		free(ret);
		free(ap);
		return (join);
	}
	else if (c[i][j - 1] > c[i - 1][j])
		return (ft_lcs_backtrack(c, s1, i, j - 1));
	else
		return (ft_lcs_backtrack(c, s1, i - 1, j));
}

char	*ft_lcs(char *s1, char *s2)
{
	int		**count;
	char	*lcs;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	count = ft_lcs_len(s1, s2);
	lcs = ft_lcs_backtrack(count, s1, ft_strlen(s1), ft_strlen(s2));
	i = ft_strlen(s1) + 1;
	while (i--)
		free(count[i]);
	free(count);
	return (lcs);
}
