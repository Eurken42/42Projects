/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:34:20 by coder             #+#    #+#             */
/*   Updated: 2022/03/15 15:08:13 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix(t_stack **a, t_stack **b)
{
	int	i;
	int	j;

	i = 0;
	while (check_sort((*a), (*a)->bot) == 0 && i <= 8)
	{
		j = -1;
		while (++j <= (*a)->bot)
		{
			if ((((*a)->stack[(*a)->top] >> i) & 1) == 1)
				ra(a);
			else
				pb(a, b);
		}
		check_empty((*a), (*b));
		while ((*b)->empty == 0)
		{
			pa(a, b);
			check_empty((*a), (*b));
		}
		i++;
	}
}

void	rrr(t_stack **a, t_stack **b)
{
	int	tmp;
	int	i;

	if ((*a)->bot > 1)
	{
		i = (*a)->bot + 1;
		tmp = (*a)->stack[i - 1];
		while (--i > (*a)->top)
			(*a)->stack[i] = (*a)->stack[i - 1];
		(*a)->stack[i] = tmp;
	}
	if ((*b)->bot > 1)
	{
		i = (*b)->bot + 1;
		tmp = (*b)->stack[i - 1];
		while (--i > (*b)->top)
			(*b)->stack[i] = (*b)->stack[i - 1];
		(*a)->stack[i] = tmp;
	}
	write(1, "rrr\n", 4);
}

void	pb_less(t_stack **a, t_stack **b, int smallest, int k)
{
	int	i;
	int	i_small;

	i = (*a)->top - 1;
	while (++i <= (*a)->bot)
	{
		if (smallest > (*a)->stack[i])
		{
			smallest = (*a)->stack[i];
			i_small = i;
		}
	}
	if (i_small < ((*a)->bot / 2))
	{
		while (i_small-- > k)
			ra(a);
		pb(a, b);
	}
	else
	{
		while (i_small++ <= (*a)->bot)
			rra(a);
		pb(a, b);
	}
}

/*int	get_small(t_stack **a, int small, int smallest)
{
	int	i;

	i = (*a)->top - 1;
	while (++i <= (*a)->bot)
		if (small > (*a)->stack[i] && smallest < (*a)->stack[i])
			small = (*a)->stack[i];
	return (small);
}

void	swap(t_stack **a, t_stack **b)
{
	pa(a, b);
	sa(a, b);
	pb(a, b);
	sb(a, b);
	pb(a, b);
}

void	solve_it(t_stack **a, t_stack **b, int *tiny, int nb)
{
	int	tmp;
	int	j;
	int	k;

	j = -1;
	while (++j < 4)
	{
		tmp = (*a)->stack[(*a)->top];
		k = -1;
		while (++k < 4)
		{
			if (tmp == tiny[k])
			{
				if ((*b)->top < (*b)->bot - 1 && tmp < (*b)->stack[(*b)->top] 
				&& tmp < (*b)->stack[(*b)->top + 1])
					swap(a, b);
				else
					pb(a, b);
			}
			else
				j = 6;
			if ((*b)->top < (*b)->bot 
			&& (*b)->stack[(*b)->top] < (*b)->stack[(*b)->top + 1])
				sb(a, b);
		}
	}
	ra_or_rra(a, nb);
}

void	ra_or_rra(t_stack **a, int nb)
{
	if (nb == 1)
		ra(a);
	else
		rra(a);
}*/