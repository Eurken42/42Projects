/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:26:21 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/15 17:08:02 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *nptr)
{
	int			neg;
	int			k;
	int			i;
	long int	res;

	i = 0;
	k = 0;
	neg = 1;
	res = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			neg *= -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i++] - '0');
		if ((res * neg) > INT_MAX || (res * neg) < INT_MIN)
			error();
		k = 1;
	}
	if (k == 0)
		error();
	return ((int)res * neg);
}

int	count_split(char **argum)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (argum[++j])
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	t_stack	*st_a;
	t_stack	*st_b;
	int		count;
	int		nb;

	nb = 1;
	count = (ac - 1);
	if (ac == 1)
		exit(EXIT_FAILURE);
	else if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		count = count_split(av);
		nb = 0;
	}
	init_stack(&st_a, &st_b, count);
	cpy_args(&st_a, av + nb, count);
	check_double(st_a, count);
	if (check_sort(st_a, st_a->bot) == 0)
		solve(&st_a, &st_b, count);
	if (st_a->stack[st_a->top] > st_a->stack[st_a->top + 1])
		sa(&st_a);
	free_all(&st_a, &st_b);
	return (0);
}
