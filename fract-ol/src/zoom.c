/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:52:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 15:03:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	big_zoom(t_fractol *d, void (*zoom)(t_fractol *d))
{
	int	i;

	i = 0;
	while (i++ <= 10)
		zoom(d);
}

void	zoom_down(t_fractol *d)
{
	d->iter -= d->iter_incr;
	d->x2 += d->zoom;
	d->y2 += d->zoom;
	d->x1 -= d->zoom;
	d->y1 -= d->zoom;
	d->zoom *= d->out;
}

void	zoom_up(t_fractol *d)
{
	if ((d->y2 - (d->zoom * d->in)) - (d->y1 - (d->zoom * d->in)) >= +0.00)
	{
		d->zoom *= d->in;
		d->iter += d->iter_incr;
		d->x2 -= d->zoom;
		d->y2 -= d->zoom;
		d->x1 += d->zoom;
		d->y1 += d->zoom;
	}
}

void	new_form(t_fractol *d)
{
	d->out = 100 / (100 * d->in);
	reset_image(d);
	if (ft_strcmp(d->set, "mandelbrot") == 0)
		mandelbrot(d);
	else
		julia(d);
}
