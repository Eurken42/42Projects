/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:09:28 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/23 15:43:15 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	nb_spc(const char *text, char set)
{
	int	i;

	i = 0;
	while (text[i] && text[i] != set)
		i++;
	return (i + 1);
}

int	ft_strchr_door(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '2')
			return (i);
	return (-1);
}

int	ft_strchr_player(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			return (i);
	return (-1);
}

int	ft_dist_wall(const float nb, const int dist)
{
	if (nb < 0)
		return (-dist);
	else
		return (dist);
}

float	ft_get_pos(const t_map *map)
{
	if (map->pos == 'N')
		return (PI * 3 / 2);
	else if (map->pos == 'S')
		return (PI / 2);
	else if (map->pos == 'W')
		return (PI);
	else if (map->pos == 'E')
		return (PI * 2);
	return (0);
}
