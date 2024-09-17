/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:44:58 by gluisier          #+#    #+#             */
/*   Updated: 2022/03/28 21:24:24 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_stack	*ft_stack_new(t_dblst *content)
{
	t_stack	*stack;

	stack = ft_calloc(1, sizeof(*stack));
	if (!stack)
		return (NULL);
	stack->first = content;
	stack->last = ft_dblst_last(content);
	return (stack);
}

void	ft_stack_destroy(t_stack **stack, void (*del)(void *))
{
	t_stack	*s;

	if (!stack || !*stack)
		return ;
	s = *stack;
	ft_dblst_clear(&(s->first), del);
	free(s);
	*stack = NULL;
}

size_t	ft_stack_size(t_stack *stack)
{
	if (!stack || !stack->first)
		return (0);
	return (ft_dblst_size(stack->first));
}

void	ft_stack_push(t_stack *stack, t_dblst *new)
{
	if (!stack || !new)
		return ;
	ft_dblst_addfront(&(stack->first), new);
	if (!stack->last)
		stack->last = new;
}

t_dblst	*ft_stack_pop(t_stack *stack)
{
	t_dblst	*pop;

	if (!stack || !stack->first)
		return (NULL);
	pop = stack->first;
	stack->first = pop->next;
	if (stack->first)
		stack->first->prev = NULL;
	else
		stack->last = NULL;
	pop->next = NULL;
	pop->prev = NULL;
	return (pop);
}
