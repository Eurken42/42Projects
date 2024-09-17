/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:36:30 by coder             #+#    #+#             */
/*   Updated: 2022/03/15 17:05:09 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **a)
{
	int	tmp;

	if ((*a)->bot >= 1)
	{
		tmp = (*a)->stack[(*a)->top];
		(*a)->stack[(*a)->top] = (*a)->stack[(*a)->top + 1];
		(*a)->stack[(*a)->top + 1] = tmp;
		write(1, "sa\n", 3);
	}
}

void	rra(t_stack **a)
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
		write(1, "rra\n", 4);
	}
}

void	ra(t_stack **a)
{
	int	tmp;
	int	i;

	if ((*a)->bot > 1)
	{
		i = (*a)->top - 1;
		tmp = (*a)->stack[i + 1];
		while (++i < (*a)->bot)
			(*a)->stack[i] = (*a)->stack[i + 1];
		(*a)->stack[i] = tmp;
		write(1, "ra\n", 3);
	}
}

void	rr(t_stack **a, t_stack **b)
{
	int	tmp;
	int	i;

	if ((*a)->bot > 1)
	{
		i = (*a)->top - 1;
		tmp = (*a)->stack[i + 1];
		while (++i < (*a)->bot)
			(*a)->stack[i] = (*a)->stack[i + 1];
		(*a)->stack[i] = tmp;
	}
	if ((*b)->bot > 1)
	{
		i = (*b)->top - 1;
		tmp = (*b)->stack[i + 1];
		while (++i < (*b)->bot)
			(*b)->stack[i] = (*b)->stack[i + 1];
		(*b)->stack[i] = tmp;
	}
	write(1, "rr\n", 3);
}

void	pa(t_stack **a, t_stack **b)
{
	if ((*a)->top > 0)
	{
		(*a)->top--;
		if ((*a)->empty)
			(*a)->stack[(*a)->top] = (*b)->stack[(*b)->top];
		else
			(*a)->stack[(*a)->top] = (*b)->stack[(*b)->top];
		(*b)->stack[(*b)->top] = 0;
		(*b)->top++;
		write(1, "pa\n", 3);
	}
}
