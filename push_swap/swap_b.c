/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:22:57 by coder             #+#    #+#             */
/*   Updated: 2022/03/15 17:05:40 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_stack **b)
{
	int	tmp;

	if ((*b)->bot > 2)
	{
		tmp = (*b)->stack[(*b)->top];
		(*b)->stack[(*b)->top] = (*b)->stack[(*b)->top + 1];
		(*b)->stack[(*b)->top + 1] = tmp;
		write(1, "sb\n", 3);
	}
}

void	rrb(t_stack **a)
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
		write(1, "rrb\n", 4);
	}
}

void	rb(t_stack **a)
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
		write(1, "rb\n", 3);
	}
}

void	ss(t_stack **a, t_stack **b)
{
	int	tmp;

	if ((*a)->bot >= 1)
	{
		tmp = (*a)->stack[(*a)->top];
		(*a)->stack[(*a)->top] = (*a)->stack[(*a)->top + 1];
		(*a)->stack[(*a)->top + 1] = tmp;
	}
	if ((*b)->bot >= 1)
	{
		tmp = (*b)->stack[(*a)->top];
		(*b)->stack[(*b)->top] = (*b)->stack[(*b)->top + 1];
		(*b)->stack[(*b)->top + 1] = tmp;
	}
	write(1, "ss\n", 3);
}

void	pb(t_stack **a, t_stack **b)
{
	if ((*b)->top > 0)
	{
		(*b)->top--;
		if ((*b)->empty)
			(*b)->stack[(*b)->top] = (*a)->stack[(*a)->top];
		else
			(*b)->stack[(*b)->top] = (*a)->stack[(*a)->top];
		(*a)->stack[(*a)->top] = 0;
		(*a)->top++;
		write(1, "pb\n", 3);
	}
}
