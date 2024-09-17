/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:37:53 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/23 15:39:14 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*xpm_get_pxl(t_data *img, int x, int y)
{
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return (0);
	return ((int *)(img->addr + (img->line_length * y + x
			* (img->bits_per_pixel / 8))));
}

void	set_data(t_cub3d *d)
{
	float	lineh;
	float	tyoff;

	d->ty = 0;
	d->size = d->s_map * HEIGHT / d->ray->distall;
	lineh = (d->s_map * HEIGHT) / d->ray->distall;
	d->step = d->s_map / (float)lineh;
	tyoff = 0;
	if (lineh > HEIGHT)
	{
		lineh = HEIGHT;
		tyoff = (d->size - HEIGHT) / 2.0;
	}
	d->ty = d->step * tyoff;
	d->tx = (int)(d->ray->value / (d->s_map
				/ d->tex[d->ray->n]->w)) % d->tex[d->ray->n]->w;
}
