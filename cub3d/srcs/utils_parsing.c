/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:50:46 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/26 11:00:34 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_getinfo(const char *value, char set)
{
	return (ft_strdup(value + nb_spc(value, set)));
}

static int	ft_put_int_arr(int *tab, char **split)
{
	int	i;
	int	nb;

	i = -1;
	while (split[++i])
	{
		if (i >= 3)
			return (0);
		nb = ft_atoi(split[i]);
		if (nb >= 0 && nb <= 255)
			tab[i] = nb;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi_charset(t_map *cub, int which)
{
	char	**split;
	char	*num;
	int		ret;

	num = ft_getinfo(cub->data->content, ' ');
	split = ft_split(num, ',');
	if (check_char(num) == 0 || ft_strlen_2pts(split) != 3 || nb_coma(num) != 2)
	{
		free_array(split);
		free(split);
		free(num);
		return (0);
	}
	if (which == 0)
		ret = ft_put_int_arr(cub->col_f, split);
	else
		ret = ft_put_int_arr(cub->col_c, split);
	free(num);
	free_array(split);
	free(split);
	return (ret);
}

static void	fill_space(int *new, int *j, int *k)
{
	new[*j] = 32;
	*j += 1;
	*k += 1;
}

int	*ft_create_map_int(const t_map *map)
{
	int	i;
	int	k;
	int	j;
	int	*new;

	new = calloc((map->len_x * map->len_y), sizeof(int));
	i = -1;
	j = 0;
	while (map->map[++i])
	{
		k = -1;
		while (map->map[i][++k])
		{
			if (k == map->pos_doorx && i == map->pos_doory)
				new[j] = 2;
			else if (k == map->pos_x && i == map->pos_y)
				new[j] = map->pos - '0';
			else
				new[j] = map->map[i][k] - '0';
			j++;
		}
		while (k < map->len_y)
			fill_space(new, &j, &k);
	}
	return (new);
}
