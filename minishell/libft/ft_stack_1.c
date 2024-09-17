/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:18:50 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/22 18:35:07 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_swap(t_stack *stack)
{
	t_dblst	*first;
	t_dblst	*scd;

	if (!stack || !stack->first || !stack->first->next)
		return ;
	first = ft_stack_pop(stack);
	scd = ft_stack_pop(stack);
	ft_stack_push(stack, first);
	ft_stack_push(stack, scd);
}

void	ft_stack_rotate(t_stack *stack)
{
	t_dblst	*pop;

	if (!stack || ft_stack_size(stack) < 2)
		return ;
	pop = ft_stack_pop(stack);
	stack->last->next = pop;
	pop->prev = stack->last;
	stack->last = pop;
}

void	ft_stack_rrotate(t_stack *stack)
{
	t_dblst	*last;

	if (!stack || !stack->last || !stack->last->prev)
		return ;
	last = stack->last;
	stack->last = last->prev;
	stack->last->next = NULL;
	last->prev = NULL;
	ft_stack_push(stack, last);
}
