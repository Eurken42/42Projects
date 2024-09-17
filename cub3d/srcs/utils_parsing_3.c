/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:41:18 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/25 16:22:45 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_get_path(const char *value)
{
	int	i;
	int	start;
	int	end;

	i = -1;
	start = -1;
	end = -1;
	while (value[++i])
	{
		if (value[i] != ' ' && start == -1)
			start = i;
		if (value[i] != ' ' && start != -1 && end != -1)
		{
			end = start;
			break ;
		}
		if (value[i] == ' ' && start != -1 && end == -1)
			end = i;
	}
	if (end == -1)
		end = i;
	return (ft_substr(value, start, end - start));
}

int	check_char(char *num)
{
	int	i;

	i = -1;
	while (num[++i])
		if (num[i] != ' ' && num[i] != ',' && !ft_isdigit(num[i]))
			return (0);
	return (1);
}

int	ft_strlen_2pts(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	nb_coma(const char *num)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (num[++i])
		if (num[i] == ',')
			k++;
	return (k);
}
