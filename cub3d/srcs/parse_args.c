/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:32:58 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/26 10:56:53 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <fcntl.h>

int	ft_check_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: can't open the file\n");
		return (-1);
	}
	return (fd);
}

int	ft_error(char *msg)
{
	printf("%s\n", msg);
	return (-1);
}

int	ft_check_path(const char *path)
{
	int	i;

	i = 0;
	while (*path && *path != '.')
	{
		++i;
		++path;
	}
	if (i == 0 || ft_strncmp_s(path, ".cub", 4) != 0)
		return (ft_error("Error: args -> ./cub3D [*.cub]"));
	return (1);
}

char	*parse_args(char *args, int nb)
{
	if (nb != 2)
	{
		printf("Error: args -> ./cub3D [*.cub]");
		return (NULL);
	}
	if (ft_check_path(args) == -1)
		return (NULL);
	return (args);
}

void	ft_fill_texture(t_map *cub, int fd)
{
	char	*before;
	char	*after;

	while (42)
	{
		before = get_next_line(fd);
		if (!before && cub->len_x == 0)
			printf("Error: map empty\n");
		if (before)
		{
			after = ft_strdup_nl(before, ft_strlen(before));
			free(before);
			if (after)
			{
				if (search_and_add(cub, after) == 0)
					break ;
			}
			else if (cub->len_x > 6)
				cub->ok = 0;
		}
		else
			break ;
	}
}
