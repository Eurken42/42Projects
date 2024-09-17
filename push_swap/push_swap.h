/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:40:15 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/15 17:06:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>

typedef struct t_stack
{
	int	*stack;
	int	empty;
	int	top;
	int	bot;
}	t_stack;

char	**ft_malloc_error(char **tab);
int		ft_get_nb_strs(char const *s, char c);
void	ft_get_next_str(char **next_str, int *next_str_len, char c);
void	pb_less(t_stack **a, t_stack **b, int smallest, int k);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		count_split(char **argum);
void	simplify_stack(t_stack **a);
int		ft_atoi(const char *nptr);
void	replace_value(t_stack **a, int *tab);

void	radix(t_stack **a, t_stack **b);
void	sb(t_stack **b);
void	rrb(t_stack **a);
void	rb(t_stack **a);
void	ss(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);

void	sa(t_stack **a);
void	rra(t_stack **a);
void	rrr(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rr(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);

void	solve(t_stack **a, t_stack **b, int count);
void	solve_3(t_stack **a, t_stack **b);
void	solve_5(t_stack **a, t_stack **b);

int		check_sort(t_stack *a, int num);
void	check_empty(t_stack *a, t_stack *b);
void	check_double(t_stack *s, int count);

void	error(void);
void	put_str(char *str);
void	free_stack(t_stack *freed);
void	swap(t_stack **a, t_stack **b);
void	free_all(t_stack **s1, t_stack **s2);
void	draw_stack(t_stack *s1, t_stack *s2, int count);
void	init_stack(t_stack **init, t_stack **init_2, int count);
void	cpy_args(t_stack **stack_cpy, char **args, int count);

/*void	ra_or_rra(t_stack **a, int nb);
void	pb_less2(t_stack **a, t_stack **b, int smallest);
void	solve_100(t_stack **a, t_stack **b);
void	solve_it(t_stack **a, t_stack **b, int *tiny, int nb);
void	check_5last(t_stack **b, t_stack **a);
int		*cpy_array(t_stack *a, int *dest);
int		get_small(t_stack **a, int small, int smallest);*/

#endif
