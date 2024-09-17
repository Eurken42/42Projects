/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:03:36 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/26 10:39:07 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_cub3d *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_cub3d *d, int x, int y, int color)
{
	int	i;
	int	j;

	j = -1;
	while (++j <= d->m_map)
	{
		i = -1;
		while (++i <= d->m_map)
			my_mlx_pixel_put(d, x + j, y + i, color);
	}
}

void	draw_line_3d(t_cub3d *mini, float lineh, float lineo)
{
	float	ok;
	int		size;

	size = HEIGHT;
	if (lineo < 0)
		lineo = 0;
	ok = lineo + lineh;
	if (ok > size)
		ok = size;
	draw_column(mini, lineo, ok);
}

char	*ft_getpath_cursor(char *s1)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin("./asset/cursor/xpm/", s1);
	free(s1);
	result = ft_strjoin(tmp, "_cursor.XPM");
	free(tmp);
	return (result);
}
