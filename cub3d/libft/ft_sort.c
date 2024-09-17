/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:19:45 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/15 20:50:37 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static void	_merge(int *ar, size_t s, size_t e, int *tmp1)
{
	int		*tmp2;

	tmp2 = tmp1 + (e - s) / 2 + 1;
	while (s < e)
	{
		if (*tmp1 < *tmp2)
		{
			ar[s] = *tmp1;
			++tmp1;
		}
		else
		{
			ar[s] = *tmp2;
			++tmp2;
		}
		++s;
	}
}

static void	_mergesort(int *ar, size_t s, size_t e)
{
	size_t	m;
	int		*tmp;

	if (e - s <= 1)
		return ;
	m = (s + e) / 2;
	_mergesort(ar, s, m);
	_mergesort(ar, m, e);
	tmp = ft_calloc(e - s + 2, sizeof(*ar));
	ft_memcpy(tmp, ar + s, (m - s) * sizeof(*ar));
	ft_memcpy(tmp + (m - s + 1), ar + m, (e - m) * sizeof(*ar));
	tmp[m - s] = INT_MAX;
	tmp[e - s + 1] = INT_MAX;
	_merge(ar, s, e, tmp);
	free(tmp);
}

void	ft_mergesort(int *ar, size_t size)
{
	_mergesort(ar, 0, size);
}
