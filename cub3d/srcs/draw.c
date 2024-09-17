/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:03:36 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/24 17:20:11 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	map_3d(t_cub3d *mini)
{
	float	lineh;
	float	lineo;
	float	ca;

	ca = mini->angle - mini->ray->ra;
	ca = fix_angle(ca);
	mini->ray->distall = mini->ray->distall * cos(ca);
	lineh = (mini->s_map * HEIGHT) / mini->ray->distall;
	lineo = 359 - lineh / 2;
	draw_line_3d(mini, lineh, lineo);
}

static void	draw_map_2d(t_cub3d *d)
{
	int	xo;
	int	yo;
	int	y;
	int	x;

	x = -1;
	while (++x < d->map->len_x)
	{
		y = 0;
		while (y < d->map->len_y)
		{
			yo = y * d->m_map;
			xo = x * d->m_map;
			if (d->map->mapeu[x * d->map->len_y + y] == 1)
				draw_square(d, yo, xo, 0x00FF0000);
			else if (d->map->mapeu[x * d->map->len_y + y] == 2)
				draw_square(d, yo, xo, 0x0099CCFF);
			else if (d->map->mapeu[x * d->map->len_y + y] == 0)
				draw_square(d, yo, xo, 0x00FFFFFF);
			else
				draw_square(d, yo, xo, 0x0099FFFF);
			y++;
		}
	}
}

static void	draw_ray(t_cub3d *d)
{
	t_raycasting	*r;

	r = ft_create_casting();
	r->d = d;
	d->ray = r;
	r->ra = d->angle - DR * (1024 / 2 / 2);
	r->ra = fix_angle(r->ra);
	r->r = 0;
	while (r->r < 1024 / 2)
	{
		ray_vert(d, r);
		ray_horizon(d, r);
		shortest_ray(r);
		map_3d(d);
		r->ra += DR;
		r->ra = fix_angle(r->ra);
		r->r++;
	}
	free(r);
}

static void	draw_cursor(t_cub3d *d)
{
	t_data	cur;
	int		size;
	char	*num;
	char	*path;
	int		px;

	px = d->s_map / d->m_map;
	size = 3;
	num = ft_itoa((int)(d->angle * 180 / PI));
	path = ft_getpath_cursor(num);
	cur.img = mlx_xpm_file_to_image(d->mlx, path, &size, &size);
	free(path);
	if (cur.img)
	{
		cur.addr = mlx_get_data_addr(cur.img, &cur.bits_per_pixel,
				&cur.line_length, &cur.endian);
		mlx_put_image_to_window(d->mlx, d->mlx_win, cur.img,
			d->px / px - 4, d->py / px - 4);
		mlx_destroy_image(d->mlx, cur.img);
	}
}

void	window(t_cub3d *d)
{
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH + 1, HEIGHT + 1);
	if (d->img)
	{
		d->addr = mlx_get_data_addr(d->img, &d->bits_per_pixel,
				&d->line_length, &d->endian);
		draw_ray(d);
		draw_map_2d(d);
		mlx_put_image_to_window(d->mlx, d->mlx_win, d->img, 0, 0);
		draw_cursor(d);
	}
}
