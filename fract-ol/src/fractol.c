/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:42:37 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 16:47:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_win(t_fractol *mini)
{
	mini->mlx = mlx_init();
	mini->win = mlx_new_window(mini->mlx, H, W, "Fract-ol");
	mini->img = mlx_new_image(mini->mlx, H, W);
	mini->color = 45201984;
	if (ft_strcmp(mini->set, "mandelbrot") == 0)
	{
		init_mandel(mini);
		mandelbrot(mini);
	}
	else
	{
		init_julia(mini);
		julia(mini);
	}
}

void	reset_image(t_fractol *d)
{
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, H, W);
}

int	die(t_fractol *d, char *str)
{
	free(d);
	ft_putstr(str);
	return (1);
}

int	main(int ac, char **av)
{
	t_fractol	*mini;

	mini = (t_fractol *) malloc(sizeof(t_fractol));
	if (ac != 2 || match(mini, av[1]) == 0)
		return (die(mini, "error: ./fractol JULIA OR MANDELBROT"));
	init_win(mini);
	mlx_hook(mini->win, 17, 0L, clean_exit, mini);
	mlx_mouse_hook(mini->win, mouse_hook, mini);
	mlx_key_hook(mini->win, key_hook, mini);
	mlx_hook(mini->win, 6, 0, &mouse_move, mini);
	mlx_loop(mini->mlx);
}
