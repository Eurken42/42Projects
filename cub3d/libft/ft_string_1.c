/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:38:16 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/05 18:13:17 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = 0;
	while (*src)
	{
		if (dstsize > 1)
		{
			*dst++ = *src;
			--dstsize;
		}
		++srclen;
		++src;
	}
	if (dstsize)
		*dst = 0;
	return (srclen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = 0;
	while (*dst)
	{
		if (dstsize)
		{
			--dstsize;
			++len;
		}
		++dst;
	}
	while (*src)
	{
		if (dstsize > 1)
		{
			*dst++ = *src;
			--dstsize;
		}
		++len;
		++src;
	}
	if (dstsize)
		*dst = 0;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n - 1 && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
		--n;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (ft_strncmp(needle, "", 2) == 0)
		return ((char *)haystack);
	while (len && *haystack)
	{
		i = 0;
		while (i < len && needle[i] && needle[i] == haystack[i])
			++i;
		if (!needle[i])
			return ((char *)haystack);
		++haystack;
		--len;
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*s;

	len = ft_strlen(str);
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str, len + 1);
	return (s);
}
