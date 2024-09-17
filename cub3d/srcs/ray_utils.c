/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:16:55 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/23 14:38:10 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	wall_hit(t_cub3d *d, t_raycasting *r, char wall)
{
	if (wall == 'H')
	{
		r->hx = r->rx;
		r->hy = r->ry;
		r->old = r->mp;
		r->disth = dist(d->px, d->py, r->hx, r->hy);
	}
	else if (wall == 'V')
	{
		r->vx = r->rx;
		r->vy = r->ry;
		r->old2 = r->mp;
		r->distv = dist(d->px, d->py, r->vx, r->vy);
	}
}

void	find_pos(t_cub3d *d, t_raycasting *r, int len)
{
	int	nb;

	nb = bitshift(d->s_map);
	r->mx = (int)(r->rx) >> nb;
	r->my = (int)(r->ry) >> nb;
	r->mp = r->my * len + r->mx;
}

float	fix_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	bitshift(const int nb)
{
	int	i;
	int	tmp;

	tmp = nb;
	i = -1;
	while (tmp)
	{
		i++;
		tmp = tmp >> 1;
	}
	return (i);
}
