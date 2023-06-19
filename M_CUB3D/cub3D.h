/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:23:21 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/19 20:43:51 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 10
# define FOV 60
# define FOV 60	
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <sys/fcntl.h>
# include <unistd.h> 
# include"get_next_line.h"
# include <string.h>

typedef struct s_map
{
	int		map_height;
	int		map_width;
	int		map_skip;
	int		ceil_hex;
	int		floor_hex;
	char	**lines;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_textures
{
	t_img	no_text;
	t_img	so_text;
	t_img	we_text;
	t_img	ea_text;
}	t_textu;

typedef struct s_keys
{
	int	a;
	int	d;
	int	w;
	int	s;
	int	r_left;
	int	r_right;
	int	event;

}	t_keys;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	int		width;
	int		height;
	int		tile;
	double	x_p;
	double	y_p;
	double	p_ang;
	int		wall_clr;
	int		x_hit;
	int		y_hit;
	double	ray_ang;
	int		v;
	t_keys	keys;
	t_map	map;
	t_textu	text;
}	t_mlx;

typedef struct s_tracing
{
	double	n_x;
	double	n_y;
	double	x_step;
	double	y_step;
	int		is_up;
	int		is_left;
	double	dis;
}	t_rtrace;

//------------get_next_line---------------
char	*get_strnjoin(char *s1, char *s2, ssize_t i);
char	*get_next_line(int fd);
//--------------PARSING------------------------------

int		parse_map(char *file, t_map *map);
int		texture_check(int fd, t_map *map, int *all_tx);
int		get_color(char *line, int *n);
int		if_map_closed(int fd, t_map *map);
int		empty_line(char *line);
void	free_text(t_map map);

//---------------utils------------------
void	p_err(char *line, int f_exit);
ssize_t	ft_strlen(char *str);
char	*ft_strncpy(char *dst, char *src, ssize_t dstsize);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *str);
int		ft_strchr(char c, char *ref);
int		ft_atoi(char *str);
int		ft_strchr(char c, char *ref);
char	**ft_split(char *s, char c);
void	free_words(char **words);
int		ft_open(char *file);
//------------------------------------------------

//-------------init--------------------------
void	find_player(t_mlx *mlxs);
t_mlx	initialize_t_mlx(t_map map);
t_map	initialize_t_map(void);
t_textu	init_text(t_map map, void *mlx);
void	destroy_mlx(t_mlx *mlxs, int img, int win);
//-------------------------------------------

void	draw_rays(t_mlx mlxs);//----------------

//-----------------angle------------------------
double	to_rad(double degree);
double	normalize_ang(double ang);

//-----------------DRAW-----------------------
void	render(t_mlx mlxs);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_floor(t_mlx mlxs, double x, double y, double h);
void	draw_ceil(t_mlx mlxs, double x, double y, double h);
void	get_wall_height(t_mlx mlxs, double dis, double *yi, double *height);

//--------------events--------------------
int		ft_key_hook(t_mlx *mlxs);
int		relase(int key, t_mlx *mlxs);
int		move_player(int key, t_mlx *mlxs);
int		ft_exit(t_mlx *mlxs);

//---------------------ray_casting---------------------------
void	cast_rays(t_mlx *mlxs, int col, int is_up, int is_left);
void	wall_projection(t_mlx mlxs, double dis, int col);
void	get_data_img(t_img	*img);
int		mlx_get_color(t_img img, int x, int y);
double	calcul_distance(t_mlx mlxs, t_rtrace ray);

#endif
