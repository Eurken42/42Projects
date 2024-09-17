/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:31:13 by coder             #+#    #+#             */
/*   Updated: 2022/03/15 14:52:56 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_double(t_stack *s, int count)
{
	int	check;
	int	i;
	int	j;

	check = 0;
	i = -1;
	while (++i < count)
	{
		j = -1;
		while (++j < count)
			if (i != j)
				if (s->stack[i] == s->stack[j])
					check = 1;
	}
	if (check == 1)
		error();
}

void	check_empty(t_stack *a, t_stack *b)
{
	if (a->top > a->bot)
		a->empty = 1;
	else
		a->empty = 0;
	if (b->top > b->bot)
		b->empty = 1;
	else
		b->empty = 0;
}

int	check_sort(t_stack *a, int num)
{
	int	i;
	int	*save;
	int	k;
	int	j;

	i = -1;
	j = 0;
	save = (int *) malloc(sizeof(int) * num);
	save[0] = a->stack[0];
	while (++i <= num)
	{
		k = -1;
		save[j] = a->stack[i];
		while (++k <= j)
		{
			if (a->stack[i] < save[k])
			{
				free(save);
				return (0);
			}
		}
		j++;
	}
	free(save);
	return (1);
}

/*void	check_5last(t_stack **b, t_stack **a)
{
	int	*test;
	int	i;
	int	j;
	int	k;
	int	w;

	j = 1;
	k = 0;
	if ((*b)->top <= (*b)->bot - 6)
	{
		test = (int *) malloc(sizeof(int) * 6);
		i = -1;
		while (j <= 5)
		{
			i = -1;
			while (++i < 6)
				test[i] = (*b)->stack[(*b)->top + i];
			if (test[j] > test[k])
			{
				w = k + 1;
				while (--w != 0)
					rb(b);
				sb(a, b);
				w = k + 1;
				while (--w != 0)
					rrb(b);
			}
			j++;
			k++;
		}
		free(test);
	}
}*/