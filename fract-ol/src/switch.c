/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:52:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 15:03:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	form_switch(t_fractol *d, int keycode)
{
	if (keycode == PAD_KEY_ONE && ft_strcmp(d->set, "julia") == 0)
		init_julia(d);
	else if (keycode == PAD_KEY_TWO && ft_strcmp(d->set, "julia") == 0)
	{
		d->in = 0.9329202111295;
		d->out = 100 / (100 * d->in);
		d->c_r = 0.285;
		d->c_i = 0.01;
		d->iter_incr = 0.55;
		d->fluid = 0;
		reset_view_julia(d);
	}
	else if (keycode == PAD_KEY_THREE && ft_strcmp(d->set, "julia") == 0)
	{
		reset_view_julia(d);
		if (d->fluid == 0)
			d->fluid = 1;
		else
			d->fluid = 0;
	}
}

void	set_switch(t_fractol *d)
{
	if (ft_strcmp(d->set, "julia") == 0)
	{
		d->set = "mandelbrot";
		init_mandel(d);
	}
	else
	{
		d->set = "julia";
		d->fluid = 0;
		init_julia(d);
	}
	new_form(d);
}

void	reset_view_julia(t_fractol *d)
{
	d->zoom = 0.1;
	d->iter = 75;
	d->x1 = -1.420762;
	d->x2 = 0.890762;
	d->y1 = -1.390762;
	d->y2 = 1.390762;
}

void	color_switch(t_fractol *d, int keycode)
{
	if (keycode == KEY_ONE)
		d->color = 12923551;
	else if (keycode == KEY_TWO)
		d->color = 10599115;
	else if (keycode == KEY_THREE)
		d->color = 27599115;
	else if (keycode == KEY_FOUR)
		d->color = 5099115;
}
