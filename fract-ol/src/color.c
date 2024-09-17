/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:31:42 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/25 14:25:45 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_tab(t_fractol **d)
{
	int				i;
	unsigned int	tmp;

	i = -1;
	if ((*d)->color <= 0)
		(*d)->color = 9000321;
	if ((*d)->iter < 0)
		(*d)->iter = 0;
	tmp = (*d)->color;
	(*d)->color_tab = malloc(sizeof(unsigned int) * (int)(*d)->iter + 1);
	while (++i <= (int)(*d)->iter)
	{
		(*d)->color_tab[i] = (*d)->color;
		if (i % 2 == 0)
			(*d)->color *= 0.999;
	}
	(*d)->color = tmp;
	(*d)->color_tab[i - 1] = tmp;
}

void	draw_tab(t_fractol *d)
{
	d->buf[d->px + 0] = (d->color_tab[d->i]) & 0xFF;
	d->buf[d->px + 1] = (d->color_tab[d->i] >> 8) & 0xFF;
	d->buf[d->px + 2] = (d->color_tab[d->i] >> 16) & 0xFF;
	d->buf[d->px + 3] = (d->color_tab[d->i] >> 24);
}
