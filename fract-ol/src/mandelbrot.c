/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:16:27 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 16:41:19 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_fractol *d)
{
	init(d);
	while (d->x < H)
	{
		d->y = 0;
		while (d->y < W)
		{
			d->px = (d->y * d->line_bts) + (d->x * 4);
			d->c_r = d->x / d->zoomx + d->x1;
			d->c_i = d->y / d->zoomy + d->y1;
			d->i = algo_mandel(d);
			draw_tab(d);
			d->y++;
		}
		d->x++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

void	init(t_fractol *d)
{
	d->x = 0;
	color_tab(&d);
	d->zoomx = H / (d->x2 - d->x1);
	d->zoomy = W / (d->y2 - d->y1);
	d->buf = mlx_get_data_addr(d->img, &d->px_bts, &d->line_bts, &d->endian);
}

void	init_mandel(t_fractol *d)
{
	d->zoom = 0.1;
	d->fluid = 0;
	d->x1 = -2.25;
	d->x2 = 0.75;
	d->y1 = -1.5;
	d->y2 = 1.5;
	d->iter = 40;
	d->in = 0.9375;
	d->out = 100 / (100 * d->in);
	d->iter_incr = 0.25;
}

int	algo_mandel(t_fractol *brot)
{
	double	i;
	double	z_r;
	double	z_i;
	double	tmp;

	i = 0;
	z_r = 0;
	z_i = 0;
	while ((((z_r * z_r) + (z_i * z_i)) < 4 && i <= brot->iter) || i == 0)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + brot->c_r;
		z_i = 2 * z_i * tmp + brot->c_i;
		i++;
	}
	return (i - 1);
}
