#include "cub3D.h"
#include <math.h>

t_img	get_text_clr(t_mlx mlxs)
{
	t_img	text;

	if (mlxs.v)
	{
		if (mlxs.ray_ang >= M_PI / 2 && mlxs.ray_ang <= (3 * M_PI) / 2)
			text = mlxs.text.we_text;
		else
			text = mlxs.text.ea_text;
	}
	else
	{
		if (mlxs.ray_ang > 0 && mlxs.ray_ang <= M_PI)
			text = mlxs.text.so_text;
		else
			text = mlxs.text.no_text;
	}
	return (text);
}

void	draw_rect(t_mlx mlxs, double x_s, double y_s, double h)
{
	double	y;
	double	y_wall;
	int		x_offset;
	int		y_offset;
	t_img	text;

	text = get_text_clr(mlxs);
	x_offset = fmod(mlxs.x_hit , mlxs.tile) * ((double)text.width / mlxs.tile);
	if (mlxs.v)
		x_offset = fmod(mlxs.y_hit , mlxs.tile) * ((double)text.width / mlxs.tile);
	y = 0;
	while (y < h && y < mlxs.height)
	{
		y_wall = y_s - (((double)mlxs.height / 2) - (h / 2));
		y_offset = y_wall * ((double)text.height / h);
		mlxs.wall_clr = mlx_get_color(text, x_offset, y_offset);
		my_mlx_pixel_put(&mlxs.img, x_s, y_s, mlxs.wall_clr);
		y++;
		y_s++;
	}
}

void	draw_floor_or_ceil(t_mlx mlxs, double x, double y, double h, int color)
{
	while (y < h)	
	{
		my_mlx_pixel_put(&mlxs.img, x, y, color);
		y++;
	}
}


void	wall_projection(t_mlx mlxs, double dis, int col)
{
	double	dis_plan;
	double	wall_height;
	double 	corr_dis;
	double 	half_width;
	double	yi;

	corr_dis = dis * cos(mlxs.ray_ang - mlxs.p_ang);
	dis = corr_dis;
	half_width = (double)mlxs.width / 2;
	dis_plan = half_width / tan(to_rad(FOV / 2));
	// wall_height = (mlxs.tile / dis) * dis_plan;
	wall_height = (mlxs.tile / dis) * mlxs.height;
	yi = ((double)mlxs.height / 2) - (wall_height / 2);
	if (yi < 0)
		yi = 0;
	if (wall_height >= mlxs.height)
		draw_rect(mlxs, col, 0, wall_height); 
	else
	{
		draw_rect(mlxs, col, yi,wall_height); 
		draw_floor_or_ceil(mlxs, col, 0, yi, mlxs.map.ceil_hex);
		draw_floor_or_ceil(mlxs, col, yi + wall_height, mlxs.height, mlxs.map.floor_hex); 
	}
}