/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:56:30 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/24 16:01:01 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <limits.h>

t_hitbox	*ft_create_hitbox(const t_cub3d *d, int px)
{
	t_hitbox	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->yo = ft_dist_wall(d->dy, px);
	new->xo = ft_dist_wall(d->dx, px);
	new->ipx = d->px / d->s_map;
	new->ipx_add_xo = (d->px + new->xo) / d->s_map;
	new->ipx_sub_xo = (d->px - new->xo) / d->s_map;
	new->ipy = d->py / d->s_map;
	new->ipy_add_yo = (d->py + new->yo) / d->s_map;
	new->ipy_sub_yo = (d->py - new->yo) / d->s_map;
	new->xo = ft_dist_wall(d->dy, px);
	new->yo = ft_dist_wall(d->dx, px);
	new->ipx_add_xoo = (d->px + new->xo) / d->s_map;
	new->ipy_add_yoo = (d->py - new->yo) / d->s_map;
	new->ipx_sub_xoo = (d->px - new->xo) / d->s_map;
	new->ipy_sub_yoo = (d->py + new->yo) / d->s_map;
	return (new);
}

static int	to_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_opti	*ft_create_opti(t_cub3d *d, float lineo, float ok)
{
	t_opti	*new;

	new = ft_calloc(1, sizeof(*new) * 3);
	if (!new)
		return (NULL);
	new[0].id = 0;
	new[0].ok = ok;
	new[0].d = d;
	new[0].c = to_rgb(0, d->map->col_c[0], d->map->col_c[1], d->map->col_c[2]);
	new[1].id = 1;
	new[1].lineo = lineo;
	new[1].ok = ok;
	new[1].d = d;
	new[2].id = 2;
	new[2].lineo = lineo;
	new[2].d = d;
	new[2].f = to_rgb(0, d->map->col_f[0], d->map->col_f[1], d->map->col_f[2]);
	return (new);
}

t_opti_ray	*ft_create_opti_rays(t_cub3d *d)
{
	t_opti_ray	*new;

	new = ft_calloc(1, sizeof(*new) * 2);
	if (!new)
		return (NULL);
	new[0].id = 0;
	new[0].d = d;
	new[1].id = 1;
	new[1].d = d;
	return (new);
}

t_raycasting	*ft_create_casting(void)
{
	t_raycasting	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->n = EMPTY;
	new->disth = INT_MAX;
	new->distv = INT_MAX;
	return (new);
}
