/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:03:15 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/26 11:07:39 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	search_door(t_map *cub, char *after)
{
	int	ret;

	ret = ft_strchr_door(after);
	if (ret != -1 && cub->len_x > 5)
	{
		after[ret] = '0';
		cub->pos_doorx = ret;
		cub->pos_doory = cub->len_x - 6;
	}
}

static int	search_player(t_map *cub, char *after)
{
	int	ret;

	ret = ft_strchr_player(after);
	if (ret != -1 && cub->len_x > 6)
	{
		if (cub->pos_x != 0 || cub->pos_y != 0)
		{
			cub->ok = -1;
			return (0);
		}
		cub->pos_x = ret;
		cub->pos_y = cub->len_x - 6;
		cub->pos = after[cub->pos_x];
		after[cub->pos_x] = '0';
	}
	cub->len_x += 1;
	return (1);
}

int	search_and_add(t_map *cub, char *after)
{
	if (cub->ok == 0)
	{
		cub->ok = -1;
		free(after);
		return (0);
	}
	search_door(cub, after);
	ft_dblst_addback(&cub->data, ft_dblst_new(after));
	if (search_player(cub, after) == 0)
		return (0);
	if (cub->len_x > 6 && (int)ft_strlen(after) > cub->len_y)
		cub->len_y = (int)ft_strlen(after);
	return (1);
}

void	get_wall_name(char **value)
{
	value[0] = NORTH;
	value[1] = SOUTH;
	value[2] = WEST;
	value[3] = EAST;
}
