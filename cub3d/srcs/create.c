/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:17:33 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/25 15:20:22 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_s_map(const int nb1, const int nb2)
{
	int	n;

	if (nb1 > nb2)
		n = nb1;
	else
		n = nb2;
	if (n <= 20)
		return (16);
	else if (n <= 35)
		return (8);
	else
		return (4);
}

static int	load_texture(t_cub3d *new, const t_map *map)
{
	char	**path;
	int		i;

	i = -1;
	path = ltoa(map->texture_path);
	new->tex = ft_calloc(5, sizeof(*new->tex));
	load(new, path, &i);
	free_array(path);
	free(path);
	if (i != 4)
	{
		printf("Error: map wrong\n");
		return (i);
	}
	return (4);
}

t_cub3d	*ft_create_win(t_map *map)
{
	t_cub3d	*new;
	int		ret;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->mlx = mlx_init();
	new->img = NULL;
	new->mlx_win = mlx_new_window(new->mlx, WIDTH, HEIGHT, "cub3D");
	new->map = map;
	new->map->mapeu = ft_create_map_int(map);
	new->s_map = 64;
	new->m_map = ft_s_map(map->len_x, map->len_y);
	new->s_player = new->s_map / 12.8;
	new->px = map->pos_x * (new->s_map) + (new->s_map / 2);
	new->py = map->pos_y * (new->s_map) + (new->s_map / 2);
	new->angle = ft_get_pos(map);
	new->dx = cos(new->angle) * 5;
	new->dy = sin(new->angle) * 5;
	ret = load_texture(new, map);
	free_array(map->map);
	if (ret != 4)
		clean_exit(new);
	return (new);
}

t_map	*ft_create_map(int fd)
{
	t_map	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->data = NULL;
	new->len_y = 0;
	new->pos_doorx = -1;
	new->pos_doory = -1;
	new->ok = 1;
	ft_fill_texture(new, fd);
	new->len_x += 1;
	return (new);
}

t_parse	*ft_create_parse(void)
{
	t_parse	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	return (new);
}
