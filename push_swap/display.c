/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:59:49 by coder             #+#    #+#             */
/*   Updated: 2022/01/22 16:00:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	put_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	draw_stack(t_stack *s1, t_stack *s2, int count)
{
	int	i;

	i = -1;
	check_empty(s1, s2);
	if (s1->empty == 1)
		printf ("\033[31mStack A\033[0m");
	else
		printf ("\033[32mStack A\033[0m");
	if (s2->empty == 1)
		printf ("\t\t\t\033[31mStack B\033[0m\n");
	else
		printf ("\t\t\t\033[32mStack B\033[0m\n");
	while (++i <= count)
		printf("%d\t\t\t%d\t\t\t[%d]\n", s1->stack[i], s2->stack[i], i);
}

void	error(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	is_in(t_stack **a, int nb)
{
	int	i;

	i = (*a)->top - 1;
	if (i > (*a)->bot)
		return (0);
	while (++i <= (*a)->bot)
		if ((*a)->stack[i] == nb)
			return (1);
	return (0);
}
