/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:53:14 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/19 16:31:31 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	routine(t_cub3d *mini)
{
	if (mini->m == 1)
		mlx_mouse_move(mini->mlx_win, WIDTH / 2, HEIGHT / 2);
	key_hook(mini);
	window(mini);
	if (mini->m == 1)
		mlx_string_put(mini->mlx, mini->mlx_win, 880, 710, 0,
			"Press M - mouse mod");
	else
		mlx_string_put(mini->mlx, mini->mlx_win, 860, 710, 0,
			"Press M - keyboard mod");
	return (0);
}

static void	ft_mlx_hook(t_cub3d *mini)
{
	mlx_hook(mini->mlx_win, 17, 0L, clean_exit, mini);
	mlx_hook(mini->mlx_win, 2, 1L << 0, handle_press, mini);
	mlx_hook(mini->mlx_win, 3, 1L << 1, handle_release, mini);
	mlx_hook(mini->mlx_win, 6, 0L, &mouse_hook, mini);
	mlx_loop_hook(mini->mlx, routine, mini);
	mlx_loop(mini->mlx);
}

int	main(int ac, char **av)
{
	t_cub3d	*mini;
	t_map	*cub;
	char	*args;
	int		fd;

	args = parse_args(av[1], ac);
	if (!args)
		return (-1);
	fd = ft_check_file(args);
	if (fd == -1)
		return (-1);
	cub = ft_create_map(fd);
	close(fd);
	if (ft_detect_type(cub) != 0)
		free_map(cub);
	mini = ft_create_win(cub);
	ft_mlx_hook(mini);
	return (0);
}
