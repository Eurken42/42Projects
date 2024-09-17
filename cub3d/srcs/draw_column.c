/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:05:44 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/24 17:21:06 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_ceiling(t_cub3d *d, float y, int color)
{
	float	x;
	int		i;
	float	tmp;

	i = 0;
	if (y < HEIGHT)
	{
		while (++i <= 2)
		{
			x = d->ray->r * 2 + i;
			if (x < WIDTH)
			{
				tmp = y - 1;
				while (++tmp < HEIGHT)
					my_mlx_pixel_put(d, x, tmp, color);
			}
		}
	}
}

static void	draw_wall(t_cub3d *d, float lineo, float ok, int color)
{
	int		x;
	int		y;
	int		i;
	int		*ptr;

	i = -1;
	while (++i <= 2)
	{
		y = lineo;
		set_data(d);
		x = d->ray->r * 2 + i;
		if (x < WIDTH)
		{
			while (++y <= ok)
			{
				ptr = xpm_get_pxl(d->tex[d->ray->n], d->tx, d->ty);
				if (ptr)
					color = *ptr;
				else
					color = 0;
				my_mlx_pixel_put(d, x, y, color);
				d->ty += d->step;
			}
		}
	}
}

static void	draw_floor(t_cub3d *d, float y, int color)
{
	float	x;
	int		i;
	float	tmp;

	i = -1;
	if (y > 0)
	{
		while (++i <= 2)
		{
			x = d->ray->r * 2 + i;
			if (x < WIDTH)
			{
				tmp = -1;
				while (++tmp <= y)
					my_mlx_pixel_put(d, x, tmp, color);
			}
		}
	}
}

static void	*ft_thread(void *args)
{
	t_opti	*new;

	new = (t_opti *) args;
	if (new->id == 0)
		draw_ceiling(new->d, new->ok, new->c);
	if (new->id == 1)
		draw_wall(new->d, new->lineo, new->ok, 0);
	if (new->id == 2)
		draw_floor(new->d, new->lineo, new->f);
	return (NULL);
}

void	draw_column(t_cub3d *d, float lineo, float ok)
{
	int		i;
	t_opti	*fast;

	i = -1;
	fast = ft_create_opti(d, lineo, ok);
	while (++i < 3)
		pthread_create(&(fast[i].thread), NULL, &ft_thread, &(fast[i]));
	while (--i >= 0)
		pthread_join(fast[i].thread, NULL);
	free(fast);
}
