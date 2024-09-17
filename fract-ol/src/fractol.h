/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:55:07 by scorreia          #+#    #+#             */
/*   Updated: 2022/03/29 15:02:52 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# define H 700
# define W 700
# define KEY_ESCAPE	53
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define ZOOM_IN 5
# define ZOOM_OUT 4
# define FORME 3
# define ITER_UP 1
# define ITER_DOWN 2
# define PAD_KEY_ONE 83
# define PAD_KEY_TWO 84
# define PAD_KEY_THREE 85
# define BIG_ZOOM_IN 69
# define BIG_ZOOM_OUT 78

typedef struct t_fractol
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*set;
	char			*buf;
	int				px_bts;
	int				line_bts;
	int				endian;
	int				px;
	int				fluid;
	int				i;
	double			x;
	double			y;
	double			x1;
	double			y1;
	double			x2;
	double			y2;
	double			c_r;
	double			c_i;
	double			iter;
	double			zoomx;
	double			zoomy;
	double			iter_incr;
	long double		zoom;
	long double		out;
	long double		in;
	unsigned int	color;
	unsigned int	*color_tab;
}	t_fractol;

void	reset_image(t_fractol *d);
void	init_mandel(t_fractol *d);
void	draw_tab(t_fractol *d);
void	ft_putstr(char *txt);
void	mandelbrot(t_fractol *d);
void	julia(t_fractol *d);
void	init(t_fractol *d);
void	color_tab(t_fractol **d);
void	init_julia(t_fractol *d);
void	zoom_up(t_fractol *d);
void	zoom_down(t_fractol *d);
void	init_win(t_fractol *mini);
void	zoom_correction(t_fractol *d);
void	new_form(t_fractol *d);
void	move(t_fractol *d, int keycode);
void	form_switch(t_fractol *d, int keycode);
void	color_switch(t_fractol *d, int keycode);
void	big_zoom(t_fractol *d, void (*zoom)(t_fractol *d));
void	reset_view_julia(t_fractol *d);
void	set_switch(t_fractol *d);

int		mouse_move(int x, int y, t_fractol *d);
int		clean_exit(t_fractol *d);
int		algo_julia(t_fractol *jul);
int		algo_mandel(t_fractol *brot);
int		mouse_hook(int button, int x, int y, t_fractol *d);
int		key_hook(int keycode, t_fractol *d);
int		die(t_fractol *d, char *str);
int		ft_tolower(int c);
int		match(t_fractol *mini, char *txt);
int		ft_strcmp(char *s1, char *s2);

char	**ft_frac_name(void);

#endif
