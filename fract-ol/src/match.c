/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:47:23 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/23 17:10:53 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	**ft_frac_name(void)
{
	char	**fractal;

	fractal = (char **) malloc(sizeof(char *) * 2);
	fractal[0] = (char *) malloc(sizeof(char) * 5);
	fractal[1] = (char *) malloc(sizeof(char) * 10);
	fractal[0] = "julia";
	fractal[1] = "mandelbrot";
	return (fractal);
}

int	match(t_fractol *mini, char *txt)
{
	char	**fractal_name;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (txt[++i])
		txt[i] = ft_tolower(txt[i]);
	i = 0;
	fractal_name = ft_frac_name();
	while (++j < 2)
	{
		if (ft_strcmp(fractal_name[j], txt) == 0)
			i++;
	}
	free(fractal_name);
	if (i == 1)
	{
		mini->set = txt;
		return (1);
	}
	return (0);
}

void	ft_putstr(char *txt)
{
	int	i;

	i = -1;
	while (txt[++i])
		write(1, &txt[i], 1);
}
