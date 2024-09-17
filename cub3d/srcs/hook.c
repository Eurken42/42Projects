/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:39:20 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/24 16:01:41 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_up_back(t_cub3d *d, const t_hitbox *b)
{
	int	nb;

	if (d->w == 1)
	{
		nb = d->map->mapeu[b->ipy * d->map->len_y + b->ipx_add_xo];
		if (nb != 1 && nb != 2)
			d->px += d->dx * (0.05 * d->s_map / 3);
		nb = d->map->mapeu[b->ipy_add_yo * d->map->len_y + b->ipx];
		if (nb != 1 && nb != 2)
			d->py += d->dy * (0.05 * d->s_map / 3);
	}
	if (d->s == 1)
	{
		nb = d->map->mapeu[b->ipy * d->map->len_y + b->ipx_sub_xo];
		if (nb != 1 && nb != 2)
			d->px -= d->dx * (0.05 * d->s_map / 3);
		nb = d->map->mapeu[b->ipy_sub_yo * d->map->len_y + b->ipx];
		if (nb != 1 && nb != 2)
			d->py -= d->dy * (0.05 * d->s_map / 3);
	}
}

static void	move_left_right(t_cub3d *d, t_hitbox *b)
{
	int	nb;

	if (d->a == 1)
	{
		nb = d->map->mapeu[b->ipy * d->map->len_y + b->ipx_add_xoo];
		if (nb != 1 && nb != 2)
			d->px += (d->dy) * (0.05 * d->s_map / 3);
		nb = d->map->mapeu[b->ipy_add_yoo * d->map->len_y + b->ipx];
		if (nb != 1 && nb != 2)
			d->py -= (d->dx) * (0.05 * d->s_map / 3);
	}
	if (d->d == 1)
	{
		nb = d->map->mapeu[b->ipy_add_yoo * d->map->len_y + b->ipx_sub_xoo];
		if (nb != 1 && nb != 2)
			d->px -= (d->dy) * (0.05 * d->s_map / 3);
		nb = d->map->mapeu[b->ipy_sub_yoo * d->map->len_y + b->ipx_add_xoo];
		if (nb != 1 && nb != 2)
			d->py += (d->dx) * (0.05 * d->s_map / 3);
	}
}

static void	move_arrow(t_cub3d *d)
{
	if (d->l == 1)
	{
		d->angle -= 0.07;
		if (d->angle < 0)
			d->angle += 2 * PI;
		d->dx = cos(d->angle) * 5;
		d->dy = sin(d->angle) * 5;
	}
	if (d->r == 1)
	{
		d->angle += 0.07;
		if (d->angle > (2 * PI))
			d->angle -= 2 * PI;
		d->dx = cos(d->angle) * 5;
		d->dy = sin(d->angle) * 5;
	}
}

void	key_hook(t_cub3d *d)
{
	t_hitbox	*b;

	b = ft_create_hitbox(d, 10);
	if (d->esc == 1)
	{
		free(b);
		clean_exit(d);
	}
	move_up_back(d, b);
	move_left_right(d, b);
	move_arrow(d);
	free(b);
}
