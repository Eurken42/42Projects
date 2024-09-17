/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:38:55 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/24 16:57:49 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_release(int keycode, t_cub3d *d)
{
	if (keycode == W)
		d->w = 0;
	else if (keycode == S)
		d->s = 0;
	else if (keycode == A)
		d->a = 0;
	else if (keycode == D)
		d->d = 0;
	else if (keycode == ARR_L)
		d->l = 0;
	else if (keycode == ARR_R)
		d->r = 0;
	else if (keycode == E)
		d->e = 0;
	return (1);
}

static void	handle_mouse(t_cub3d *d)
{
	if (d->m == 0)
	{
		d->m = 1;
		mlx_mouse_hide();
	}
	else
	{
		d->m = 0;
		mlx_mouse_show();
	}
}

static void	handle_option(int keycode, t_cub3d *d, t_hitbox *b)
{
	int	nb;

	if (keycode == E)
	{
		if (d->e == 0)
		{
			nb = b->ipy_add_yo * d->map->len_y + b->ipx_add_xo;
			if (d->map->mapeu[nb] == 3)
				d->map->mapeu[nb] = 2;
			else if (d->map->mapeu[nb] == 2)
				d->map->mapeu[nb] = 3;
			d->e = 1;
		}
		else if (d->e == 1)
			d->e = 0;
	}
	else if (keycode == 46)
		handle_mouse(d);
}

int	handle_press(int keycode, t_cub3d *d)
{
	t_hitbox	*b;

	b = ft_create_hitbox(d, 20);
	if (keycode == W)
		d->w = 1;
	else if (keycode == S)
		d->s = 1;
	else if (keycode == A)
		d->a = 1;
	else if (keycode == D)
		d->d = 1;
	else if (keycode == ARR_L && d->m == 0)
		d->l = 1;
	else if (keycode == ARR_R && d->m == 0)
		d->r = 1;
	else if (keycode == ESC)
		d->esc = 1;
	handle_option(keycode, d, b);
	free(b);
	return (1);
}

int	mouse_hook(int x, int y, t_cub3d *d)
{
	(void) y;
	if (d->m == 1)
	{
		if (x > WIDTH / 2)
		{
			d->angle += 0.08;
			if (d->angle > (2 * PI))
				d->angle -= 2 * PI;
			d->dx = cos(d->angle) * 5;
			d->dy = sin(d->angle) * 5;
		}
		if (x < WIDTH / 2)
		{
			d->angle -= 0.08;
			if (d->angle < 0)
				d->angle += 2 * PI;
			d->dx = cos(d->angle) * 5;
			d->dy = sin(d->angle) * 5;
		}
	}
	return (1);
}
