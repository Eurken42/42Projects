/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:16:55 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/23 14:38:45 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	shortest_vertical(t_raycasting *r)
{
	if (r->ra > (PI / 2) && r->ra < (3 * PI / 2))
		r->n = WE;
	else
		r->n = ES;
	r->rx = r->vx;
	r->ry = r->vy;
	r->value = r->vy;
	r->distall = r->distv;
	r->old = r->old2;
}

void	shortest_ray(t_raycasting *r)
{
	if (r->disth < r->distv)
	{
		if (r->ra > PI)
			r->n = NO;
		else
			r->n = SU;
		r->rx = r->hx;
		r->ry = r->hy;
		r->distall = r->disth;
		r->value = r->hx;
	}
	else
		shortest_vertical(r);
	if (r->old > 0 && r->old < r->d->map->len_x * r->d->map->len_y
		&&r->d->map->mapeu[r->old] == 2)
		r->n = DOOR;
}

void	next_line(t_raycasting *r)
{
	r->rx += r->xo;
	r->ry += r->yo;
}
