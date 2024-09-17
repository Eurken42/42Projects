/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:26:52 by coder             #+#    #+#             */
/*   Updated: 2022/03/15 17:06:50 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	solve(t_stack **a, t_stack **b, int count)
{
	if (count <= 3)
		solve_3(a, b);
	else if (count <= 5)
		solve_5(a, b);
	else
	{
		simplify_stack(a);
		radix(a, b);
	}
	check_empty((*a), (*b));
}

void	solve_3(t_stack **a, t_stack **b)
{
	if ((*a)->stack[(*a)->top] > (*a)->stack[(*a)->top + 1])
		ra(a);
	if ((*a)->stack[(*a)->top] > (*a)->stack[(*a)->top + 1])
		sa(a);
	if ((*a)->stack[(*a)->top] > (*a)->stack[(*a)->bot])
		rra(a);
	if ((*a)->stack[(*a)->bot] < (*a)->stack[(*a)->bot - 1])
	{
		pb(a, b);
		sa(a);
		pa(a, b);
	}
}

void	solve_5(t_stack **a, t_stack **b)
{
	int	big;

	big = 2147483647;
	if ((*a)->bot == 4)
		pb_less(a, b, big, 0);
	pb_less(a, b, big, 1);
	solve_3(a, b);
	pa(a, b);
	pa(a, b);
}

void	simplify_stack(t_stack **a)
{
	int	i;
	int	j;
	int	pos;
	int	smallest;
	int	*index;

	j = -1;
	index = (int *) malloc(sizeof(int) * (*a)->bot);
	while (++j <= (*a)->bot)
	{
		i = -1;
		smallest = INT_MAX;
		while (++i <= (*a)->bot)
		{
			if (smallest > (*a)->stack[i])
			{
				smallest = (*a)->stack[i];
				pos = i;
			}
		}
		(*a)->stack[pos] = INT_MAX;
		index[j] = pos;
	}
	replace_value(a, index);
	free(index);
}

void	replace_value(t_stack **a, int *tab)
{
	int	i;

	i = -1;
	while (++i <= (*a)->bot)
		(*a)->stack[tab[i]] = i;
}

/*void	solve_100(t_stack **a, t_stack **b)
{
	int	big;

	big = 2147483647;
	while ((*a)->empty == 0)
	{
		pb_less2(a, b, (*a)->top);
		check_empty((*a), (*b));
	}
	while ((*b)->empty == 0)
	{
		pa(a, b);
		check_empty((*a), (*b));
	}
}

void	pb_less2(t_stack **a, t_stack **b, int smallest)
{
	int	i;
	int	j;
	int	i_small;
	int	*tiny;

	tiny = (int *) malloc(sizeof(int) * 4);
	i = -1;
	while (++i < 4)
		tiny[i] = INT_MAX;
	i = (*a)->top - 1;
	while (++i <= (*a)->bot)
	{
		if (tiny[0] > (*a)->stack[i])
		{
			tiny[0] = (*a)->stack[i];
			i_small = i;
		}
	}
	i = -1;
	j = 0;
	while (++j < 4)
		tiny[j] = get_small(a, tiny[j], tiny[++i]);
	if (i_small < ((*a)->bot - ((*a)->top) / 2))
		while (is_in(a, tiny[0]) == 1)
			solve_it(a, b, tiny, 1);
	else
		while (is_in(a, tiny[0]) == 1)
			solve_it(a, b, tiny, 0);
	check_5last(b, a);
	free(tiny);
}

int	*cpy_array(t_stack *a, int *dest)
{
	int	i;

	i = -1;
	dest = (int *) malloc(sizeof(int) * a->bot);
	while (++i < a->bot)
		dest[i] = a->stack[i];
	return (dest);
}*/
