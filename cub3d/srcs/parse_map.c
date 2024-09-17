/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:16:55 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/26 10:59:53 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_strchr_vert(char **map, int i, int j, int len)
{
	int	backup;
	int	time;

	backup = i - 1;
	time = 0;
	while (++backup <= len)
	{
		if (map[backup][j] == '1')
		{
			time++;
			break ;
		}
	}
	backup = i + 1;
	while (--backup >= 0)
	{
		if (map[backup][j] == '1')
		{
			time++;
			break ;
		}
	}
	if (time == 2)
		return (1);
	return (0);
}

static int	ft_strchr_horiz(char **map, int i, int j)
{
	int	backup;
	int	time;

	backup = j - 1;
	time = 0;
	while (++backup <= (int)ft_strlen(map[i]))
	{
		if (map[i][backup] == '1')
		{
			time++;
			break ;
		}
	}
	backup = j + 1;
	while (--backup >= 0)
	{
		if (map[i][backup] == '1')
		{
			time++;
			break ;
		}
	}
	if (time == 2)
		return (1);
	return (0);
}

static int	ft_check_zero(char **map, int i, int len, t_parse *d)
{
	if (map[i][d->j] == '0' && d->in == 1)
	{
		if (i + 1 <= len)
			if (map[i][d->j + 1] == ' ' || map[i + 1][d->j] == ' ')
				return (0);
		if (i - 1 >= 0)
			if (map[i - 1][d->j] == ' ' || map[i][d->j - 1] == ' ')
				return (0);
		if (ft_strchr_horiz(map, i, d->j) == 0)
			return (0);
		else if (ft_strchr_vert(map, i, d->j, len) == 0)
			return (0);
	}
	return (1);
}

static int	ft_qqch(char **map, t_parse *d, int i, int len)
{
	if (map[i][d->j] != ' ' && map[i][d->j] != '1' && map[i][d->j] != '0')
		return (0);
	else if (map[i][d->j] == '1' && d->in == 0)
		d->in = 1;
	else if (map[i][d->j] != '1' && map[i][d->j] != ' ' && d->in == 0)
		return (0);
	else if (map[i][d->j] == ' ' && d->in == 1)
	{
		if (!ft_strchr(map[i] + d->j, '1'))
			d->in = 0;
		else if (ft_strchr_vert(map, i, d->j, len) == 0)
			d->in = 0;
	}
	return (1);
}

int	ft_check_map_valid(char **map, int i, int len)
{
	t_parse	*d;

	d = ft_create_parse();
	while (map[++i])
	{
		d->in = 0;
		d->j = -1;
		while (map[i][++d->j])
		{
			if (ft_qqch(map, d, i, len) == 0
				|| ft_check_zero(map, i, len, d) == 0)
			{
				free(d);
				return (0);
			}
		}
	}
	free(d);
	return (1);
}
