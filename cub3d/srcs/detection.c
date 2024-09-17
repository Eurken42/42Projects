/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:45:49 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/31 15:35:20 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_detect_color(t_map *cub, int i)
{
	char	*content;
	char	*value[2];

	value[0] = FLOOR;
	value[1] = CEILING;
	i = -1;
	content = ft_substr(cub->data->content, 0, 1);
	while (++i < 2)
	{
		if (ft_strncmp_s(content, value[i], 1) == 0)
		{
			if (ft_atoi_charset(cub, i) == 0)
			{
				free(content);
				return (0);
			}
			cub->data->type = COLOR;
			free(content);
			return (1);
		}
	}
	free(content);
	return (0);
}

static int	ft_detect_texture(t_map *cub, int i, int fd)
{
	char	*value[4];
	char	*content;
	char	*path;

	get_wall_name(value);
	content = ft_substr(cub->data->content, 0, 2);
	while (++i < 4)
	{
		if (ft_strncmp_s(content, value[i], 2) == 0)
		{
			path = ft_get_path(cub->data->content + 2);
			fd = ft_check_file(path);
			free(path);
			free(content);
			if (fd == -1)
				return (0);
			close(fd);
			ft_dblst_addback(&cub->texture_path,
				ft_dblst_new(ft_strdup(cub->data->content)));
			return (1);
		}
	}
	if (content)
		free(content);
	return (0);
}

static int	ft_detect_map(t_map *cub, int i)
{
	int		ret;
	char	**map;

	map = ltoa(cub->data);
	ret = ft_check_map_valid(map, i - 1, cub->len_x - 1);
	if (ret == 0)
	{
		cub->map = NULL;
		free_array(map);
		free(map);
	}
	else
		cub->map = map;
	return (ret);
}

static int	launch_detect(t_map *cub, int i)
{
	int	fd;

	fd = 0;
	if (i < 6)
	{
		if (ft_detect_texture(cub, -1, fd) == 0 && ft_detect_color(cub, i) == 0)
			return (ft_error("Error: texture or color"));
	}
	else
	{
		if (ft_detect_map(cub, i - 6) == 0 || cub->ok == -1
			|| (cub->pos_x == 0 && cub->pos_y == 0))
			return (ft_error("Error: map wrong"));
		return (0);
	}
	return (1);
}

int	ft_detect_type(t_map *cub)
{
	t_dblst	*old;
	int		i;
	int		ret;

	i = 0;
	cub->len_x -= 7;
	old = cub->data;
	while (cub->data)
	{
		ret = launch_detect(cub, i);
		if (ret == 0 || ret == -1)
			break ;
		i++;
		cub->data = cub->data->next;
	}
	cub->data = old;
	return (ret);
}
