/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 00:06:48 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/15 10:54:31 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define VALID_MAP_CHARS "01NSEW"
# define RES_X 640
# define RES_Y 480
# define SPR_RES 64
# define MAX_WIDTH 30
# define MAX_HEIGHT 30
# define CAMERA_FOV 0.66
# define STEP 0.05
# define CAM_STEP 0.1
# define MSE_STEP 0.02

# define LEFT_ARROW 65363
# define RIGHT_ARROW 65361
# define UP_KEY 119
# define LEFT_KEY 97
// # define UP_KEY 122
// # define LEFT_KEY 113
# define DOWN_KEY 115
# define RIGHT_KEY 100
# define ESC_KEY 65307

typedef struct norm1
{
	int		dend;
	double	step;
	double	texpos;
	int		x;
	int		dstart;
	int		tpos;
	int		i;
}	t_n1;

typedef struct norm2
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	c;
}	t_n2;

typedef struct color
{
	unsigned char	red;
	unsigned char	blue;
	unsigned char	green;
}	t_color;

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_ray
{
	int		cell_x;
	int		cell_y;
	t_vect	pos;
	t_vect	dir;
	t_vect	sdst;
	t_vect	ddst;
	t_vect	step;
	double	len;
	int		side;
	int		hit;
	double	hit_offset;
	t_vect	tex;
}	t_ray;

typedef struct s_myimg
{
	int		bpp;
	int		line_size;
	int		endian;
	void	*img_ptr;
	char	*img_data;
}	t_myimg;

typedef struct s_data
{
	void			*no;
	void			*so;
	void			*we;
	void			*ea;
	unsigned char	f[3];
	unsigned char	c[3];
	char			**map;
	int				map_height;
	int				map_width;
	t_vect			player;
	t_vect			cam;
	t_vect			plane;
	void			*mlx_ptr;
	void			*win_ptr;
	t_myimg			screen;
	short			print_minimap;
}	t_data;

/***********				gnl.c									***********/
char	*gnl(int fd);

/***********				map_parsing.c							***********/
t_data	*parse_map(char *filename);

/***********				map_content_checker.c					***********/
int		is_valid_file_content(int fd);

/***********				map_map_checker.c						***********/
char	**read_map(int fd);
void	map_padding(char **map);
int		is_valid_map(int fd);

/***********				game_loop.c								***********/
void	draw_screen(t_data *d);

/***********				minimap.c								***********/
void	draw_minimap(t_data *d, int px, int py);

/***********				my_free.c								***********/
void	free_data(t_data *data);

/***********				hooks.c									***********/
int		red_cross_exit(t_data *data);
int		key_hook(int keycode, t_data *data);
int		mouse_hook(int x, int y, t_data *data);
int		mouse_lock(int x, int y, t_data *data);
void	camera_move_mouse(int keycode, t_data *d);

/***********				data_utils.c							***********/
void	set_ptrs_null(t_data *data);

/***********				ft_strstrutils.c						***********/
void	free_strstr(char **str);
int		ft_strstrlen(char **str);
char	**ft_strstrdup(char **env);

/***********				ft_strutils.c							***********/
int		ft_strisdigit(char *s);

/***********				debug.c									***********/
void	debug_print_data(t_data *data);
void	debug_print_vectors(t_data *data);

void	init_raynorm(t_ray *ray);
void	ray_lifenorm(t_ray *ray);
void	draw_norm1(t_data *d, t_n2 *n);
void	draw_norm2(t_data *d, t_n2 *n);
void	draw_norm3(t_data *d, t_n2 *n);
void	*xpm_to_image_norm(t_data *d, char	*l);
void	init_data_norm(t_data *data, int nb);
void	draw_top_norm(t_data *d, t_n1 *n);
void	draw_bot_norm(t_data *d, t_n1 *n, int dend);
void	draw_texture_norm(t_data *d, t_n1 *n, t_ray *ray, void *texture);
void	draw_texture(t_data *d, t_ray *r, void *t, t_n1 *n);

#endif
