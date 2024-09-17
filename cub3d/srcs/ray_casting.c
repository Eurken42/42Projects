/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:16:55 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/24 14:12:34 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	straight_look(t_cub3d *d, t_raycasting *r)
{
	r->rx = d->px;
	r->ry = d->py;
}

static void	look_updown(t_cub3d *d, t_raycasting *r)
{
	int	nb;

	nb = bitshift(d->s_map);
	if (r->ra > PI)
	{
		r->ry = (((int)d->py >> nb) << nb) - 0.001;
		r->rx = (d->py - r->ry) * r->atan + d->px;
		r->yo = -d->s_map;
		r->xo = -r->yo * r->atan;
	}
	else if (r->ra < PI)
	{
		r->ry = (((int)d->py >> nb) << nb) + d->s_map;
		r->rx = (d->py - r->ry) * r->atan + d->px;
		r->yo = d->s_map;
		r->xo = -r->yo * r->atan;
	}
	else
		straight_look(d, r);
}

static void	look_leftright(t_cub3d *d, t_raycasting *r)
{
	int	nb;

	nb = bitshift(d->s_map);
	if (r->ra > (PI / 2) && r->ra < (3 * PI / 2))
	{
		r->rx = (((int)d->px >> nb) << nb) - 0.001;
		r->ry = (d->px - r->rx) * r->ntan + d->py;
		r->xo = -d->s_map;
		r->yo = -r->xo * r->ntan;
	}
	else if (r->ra < (PI / 2) || r->ra > (3 * PI / 2))
	{
		r->rx = (((int)d->px >> nb) << nb) + d->s_map;
		r->ry = (d->px - r->rx) * r->ntan + d->py;
		r->xo = d->s_map;
		r->yo = -r->xo * r->ntan;
	}
	else
		straight_look(d, r);
}

void	ray_horizon(t_cub3d *d, t_raycasting *r)
{
	int	i;

	i = -1;
	r->atan = -1 / tan(r->ra);
	look_updown(d, r);
	while (++i < d->map->len_x)
	{
		find_pos(d, r, d->map->len_y);
		if (r->mp > 0 && r->mp < d->map->len_x * d->map->len_y
			&& (d->map->mapeu[r->mp] == 1 || d->map->mapeu[r->mp] == 2))
			break ;
		next_line(r);
	}
	wall_hit(d, r, 'H');
}

void	ray_vert(t_cub3d *d, t_raycasting *r)
{
	int	i;

	i = -1;
	r->ntan = -tan(r->ra);
	look_leftright(d, r);
	while (++i < d->map->len_y)
	{
		find_pos(d, r, d->map->len_y);
		if (r->mp > 0 && r->mp < d->map->len_x * d->map->len_y
			&& (d->map->mapeu[r->mp] == 1 || d->map->mapeu[r->mp] == 2))
			break ;
		next_line(r);
	}
	wall_hit(d, r, 'V');
}
