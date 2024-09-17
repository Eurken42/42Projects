/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:18:52 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/25 14:45:30 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_all(t_cub3d *d)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (d->tex[i])
			free(d->tex[i]);
	free(d->tex);
	ft_dblst_clear(&d->map->texture_path, free);
	ft_dblst_clear(&d->map->data, free);
	free(d->map->mapeu);
	free(d->map->map);
	free(d->map);
	free(d);
}

void	free_map(t_map *map)
{
	ft_dblst_clear(&map->texture_path, free);
	ft_dblst_clear(&map->data, free);
	free(map->mapeu);
	free_array(map->map);
	free(map->map);
	free(map);
	exit(0);
}

int	clean_exit(t_cub3d *d)
{
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->mlx_win);
	free_all(d);
	exit(0);
	return (0);
}
