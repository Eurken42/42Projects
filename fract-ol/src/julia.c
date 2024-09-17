/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:52:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 15:03:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_fractol *d)
{
	init(d);
	while (d->x < H)
	{
		d->y = 0;
		while (d->y < W)
		{
			d->px = (d->y * d->line_bts) + (d->x * 4);
			d->i = algo_julia(d);
			draw_tab(d);
			d->y++;
		}
		d->x++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

void	init_julia(t_fractol *d)
{
	d->zoom = 0.1;
	d->fluid = 0;
	d->x1 = -1.420762;
	d->x2 = 0.890762;
	d->y1 = -1.390762;
	d->y2 = 1.390762;
	d->iter = 50;
	d->c_r = 0;
	d->c_i = 0.8;
	d->in = 0.9329202112746;
	d->out = 100 / (100 * d->in);
	d->iter_incr = 0.25;
}

int	algo_julia(t_fractol *jul)
{
	int		i;
	double	z_r;
	double	z_i;
	double	tmp;

	i = 0;
	z_r = jul->x / jul->zoomy + jul->x1;
	z_i = jul->y / jul->zoomy + jul->y1;
	while ((((z_r * z_r) + (z_i * z_i)) < 4 && i <= jul->iter) || i == 0)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + jul->c_r;
		z_i = 2 * z_i * tmp + jul->c_i;
		i++;
	}
	return (i - 1);
}
