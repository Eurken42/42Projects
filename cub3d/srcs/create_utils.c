/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:46:44 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/31 15:22:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_index(const char *path)
{
	if (ft_strncmp(path, "NO", 2) == 0)
		return (0);
	else if (ft_strncmp(path, "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(path, "WE", 2) == 0)
		return (2);
	else if (ft_strncmp(path, "EA", 2) == 0)
		return (3);
	return (0);
}

static int	check_double(int *old)
{
	int	j;
	int	k;

	j = -1;
	while (++j < 4)
	{
		k = -1;
		while (++k < 4)
			if (k != j && old[j] == old[k])
				return (0);
	}
	return (1);
}

static int	xpm_to_img(t_cub3d *new, int *i, int index, char **path)
{
	char	*new_path;

	new_path = ft_get_path(path[*i] + 2);
	new->tex[index] = ft_calloc(1, sizeof(*new->tex[index]));
	new->tex[index]->img = mlx_xpm_file_to_image(new->mlx, new_path,
			&new->tex[index]->w, &new->tex[index]->h);
	free(new_path);
	if (!new->tex[index]->img)
		return (0);
	new->tex[index]->addr = mlx_get_data_addr(new->tex[index]->img,
			&new->tex[index]->bits_per_pixel, &new->tex[index]->line_length,
			&new->tex[index]->endian);
	return (1);
}

static void	load_wall(t_cub3d *new, char **path, int *i)
{
	int	index;
	int	old[4];

	while (++*i < 4)
	{
		index = get_index(path[*i]);
		old[*i] = index;
		if (check_double(old) != 0)
		{
			if (xpm_to_img(new, i, index, path) == 0)
				break ;
		}
		else
		{
			break ;
		}
	}
}

void	load(t_cub3d *new, char **path, int *i)
{
	load_wall(new, path, i);
	if (*i == 4)
	{
		new->tex[*i] = ft_calloc(1, sizeof(*new->tex[*i]));
		new->tex[*i]->img = mlx_xpm_file_to_image(new->mlx, "asset/door.xpm",
				&new->tex[*i]->w, &new->tex[*i]->h);
		if (!new->tex[*i]->img)
			*i = -1;
		else
			new->tex[*i]->addr = mlx_get_data_addr(new->tex[*i]->img,
					&new->tex[*i]->bits_per_pixel, &new->tex[*i]->line_length,
					&new->tex[*i]->endian);
	}
}
