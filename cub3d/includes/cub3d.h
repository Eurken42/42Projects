/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:54:57 by scorreia          #+#    #+#             */
/*   Updated: 2023/01/25 16:23:01 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

# define DR 0.002222
# define PI 3.141592653589793

# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define FLOOR "F"
# define CEILING "C"
# define WIDTH 1024
# define HEIGHT 720

# define ARR_R 124
# define ARR_L 123
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define E 14

typedef struct s_cub3d	t_cub3d;

enum e_texture {
	NO,
	SU,
	WE,
	ES,
	DOOR,
	EMPTY,
};

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
}	t_data;

typedef struct s_map
{
	t_dblst	*data;
	t_dblst	*texture_path;
	int		col_f[3];
	int		col_c[3];
	int		len_x;
	int		len_y;
	int		pos_x;
	int		pos_y;
	int		pos_doorx;
	int		pos_doory;
	char	pos;
	char	**map;
	int		*mapeu;
	int		ok;
}	t_map;

typedef struct s_raycasting
{
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				old;
	int				old2;
	float			rx;
	float			ry;
	float			ra;
	float			xo;
	float			yo;
	float			atan;
	float			ntan;
	float			disth;
	float			hx;
	float			hy;
	float			distv;
	float			vx;
	float			vy;
	float			distall;
	float			value;
	t_cub3d			*d;
	enum e_texture	n;
}	t_raycasting;

typedef struct s_hitbox
{
	int	xo;
	int	yo;
	int	ipx;
	int	ipy;
	int	ipx_add_xo;
	int	ipy_add_yo;
	int	ipx_sub_xo;
	int	ipy_sub_yo;

	int	ipx_add_xoo;
	int	ipy_add_yoo;
	int	ipx_sub_xoo;
	int	ipy_sub_yoo;
}	t_hitbox;

typedef struct s_cub3d
{
	void			*mlx_win;
	void			*mlx;
	void			*img;
	char			*addr;
	void			*cursor;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				s_map;
	int				m_map;
	int				w;
	int				s;
	int				a;
	int				d;
	int				l;
	int				r;
	int				m;
	int				e;
	int				element;
	int				esc;
	float			s_player;
	float			px;
	float			py;
	float			dx;
	float			dy;
	float			tx;
	float			ty;
	float			step;
	float			size;
	float			angle;
	t_map			*map;
	t_raycasting	*ray;
	t_data			**tex;
}	t_cub3d;

typedef struct s_parse
{
	int	j;
	int	in;
	int	pos;
}	t_parse;

typedef struct t_opti
{
	int			id;
	int			c;
	int			f;
	float		lineo;
	float		ok;
	t_cub3d		*d;
	pthread_t	thread;

}	t_opti;

typedef struct t_opti_ray
{
	int			id;
	int			c;
	int			f;
	float		lineo;
	float		ok;
	t_cub3d		*d;
	pthread_t	thread;

}	t_opti_ray;

void			window(t_cub3d *win);
void			draw_column(t_cub3d *d, float lineo, float ok);
void			draw_square(t_cub3d *d, int x, int y, int color);

int				*ft_create_map_int(const t_map *map);
t_map			*ft_create_map(int fd);
t_parse			*ft_create_parse(void);
t_cub3d			*ft_create_win(t_map *map);
t_hitbox		*ft_create_hitbox(const t_cub3d *d, int px);
t_raycasting	*ft_create_casting(void);
t_opti			*ft_create_opti(t_cub3d *d, float lineo, float ok);
t_opti_ray		*ft_create_opti_rays(t_cub3d *d);

void			free_all(t_cub3d *d);
void			free_map(t_map *map);

float			degToRad(int a);
float			fix_angle(float angle);
float			ft_get_pos(const t_map *map);

void			set_data(t_cub3d *d);
void			draw_line_3d(t_cub3d *mini, float lineh, float lineo);
void			my_mlx_pixel_put(t_cub3d *data, int x, int y, int color);
void			ray_horizon(t_cub3d *d, t_raycasting *r);
void			ray_vert(t_cub3d *d, t_raycasting *r);
void			wall_hit(t_cub3d *d, t_raycasting *r, char wall);
void			find_pos(t_cub3d *d, t_raycasting *r, int len);
void			next_line(t_raycasting *r);
void			shortest_ray(t_raycasting *r);
void			key_hook(t_cub3d *d);
void			ft_fill_texture(t_map *data, int fd);
void			load(t_cub3d *new, char **path, int *i);
void			get_wall_name(char **value);

int				search_and_add(t_map *cub, char *after);
int				check_char(char *num);
int				ft_strlen_2pts(char **str);
int				*xpm_get_pxl(t_data *img, int x, int y);
int				mouse_hook(int x, int y, t_cub3d *d);
int				handle_press(int keycode, t_cub3d *d);
int				handle_release(int keycode, t_cub3d *d);
int				bitshift(const int nb);
int				ft_dist_wall(const float nb, const int dist);
int				clean_exit(t_cub3d *d);
int				ft_error(char *msg);
int				ft_detect_type(t_map *cub);
int				ft_check_path(const char *path);
int				nb_spc(const char *text, char set);
int				nb_coma(const char *num);
int				ft_check_file(const char *filename);
int				ft_atoi_charset(t_map *cub, int which);
int				ft_check_map_valid(char **map, int i, int len);
int				ft_strchr_player(const char *str);
int				ft_strchr_door(const char *str);

char			*ft_get_path(const char *value);
char			*ft_getpath_cursor(char *s1);
char			*parse_args(char *args, int nb);
char			*ft_getinfo(const char *value, char set);

#endif
