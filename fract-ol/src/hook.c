/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:52:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 15:03:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_move(int x, int y, t_fractol *d)
{
	if (d->fluid == 1)
	{
		d->c_r = (x - (W / 2)) / 111.4649681529;
		d->c_i = (y - (W / 2)) / 111.4649681529;
		new_form(d);
	}
	return (0);
}

void	move(t_fractol *d, int keycode)
{
	if (keycode == KEY_UP)
	{
		d->y1 -= d->zoom;
		d->y2 -= d->zoom;
	}
	else if (keycode == KEY_DOWN)
	{
		d->y1 += d->zoom;
		d->y2 += d->zoom;
	}
	else if (keycode == KEY_LEFT)
	{
		d->x1 -= d->zoom;
		d->x2 -= d->zoom;
	}
	else if (keycode == KEY_RIGHT)
	{
		d->x1 += d->zoom;
		d->x2 += d->zoom;
	}
}

int	mouse_hook(int button, int x, int y, t_fractol *d)
{
	(void) x;
	(void) y;
	if (button == ZOOM_OUT)
		zoom_down(d);
	else if (button == ZOOM_IN)
		zoom_up(d);
	else if (button == FORME)
		set_switch(d);
	else if (button == ITER_UP)
		d->iter += 5;
	else if (button == ITER_DOWN)
		d->iter -= 5;
	new_form(d);
	return (0);
}

int	key_hook(int keycode, t_fractol *d)
{
	if (keycode == KEY_ESCAPE)
		clean_exit(d);
	else if (keycode >= KEY_ONE && keycode <= KEY_FOUR)
		color_switch(d, keycode);
	else if (keycode >= PAD_KEY_ONE && keycode <= PAD_KEY_THREE)
		form_switch(d, keycode);
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		move(d, keycode);
	else if (keycode == BIG_ZOOM_IN)
		big_zoom(d, zoom_up);
	else if (keycode == BIG_ZOOM_OUT)
		big_zoom(d, zoom_down);
	new_form(d);
	return (0);
}

int	clean_exit(t_fractol *d)
{
	reset_image(d);
	mlx_destroy_window(d->mlx, d->win);
	if (d->color_tab)
		free(d->color_tab);
	free(d);
	exit(1);
	return (0);
}
