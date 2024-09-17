/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:53:01 by coder             #+#    #+#             */
/*   Updated: 2022/03/15 14:07:37 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	cpy_args(t_stack **stack_cpy, char **args, int count)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (count--)
		(*stack_cpy)->stack[k++] = ft_atoi(args[i++]);
}

void	init_stack(t_stack **init, t_stack **init_2, int count)
{
	(*init) = (t_stack *) malloc(sizeof(t_stack));
	(*init)->stack = (int *) malloc(sizeof(int) * count);
	(*init)->top = 0;
	(*init)->bot = count - 1;
	(*init)->empty = 0;
	(*init_2) = (t_stack *) malloc(sizeof(t_stack));
	(*init_2)->stack = (int *) malloc(sizeof(int) * count);
	(*init_2)->bot = count - 1;
	(*init_2)->top = (*init_2)->bot + 1;
	(*init_2)->empty = 1;
}

void	free_stack(t_stack *freed)
{
	free(freed->stack);
	free(freed);
}

void	free_all(t_stack **s1, t_stack **s2)
{
	free_stack((*s1));
	free_stack((*s2));
}
