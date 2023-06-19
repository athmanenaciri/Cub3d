/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:45:27 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/19 11:17:00 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

int	get_x_offset(t_mlx mlxs, t_img text)
{
	int	x_offset;

	if (mlxs.v)
	{
		if (mlxs.ray_ang >= M_PI / 2 && mlxs.ray_ang <= (3 * M_PI) / 2)
			x_offset = fabs(fmod(mlxs.y_hit, mlxs.tile) - mlxs.tile);
		else
			x_offset = fmod(mlxs.y_hit, mlxs.tile);
	}
	else
	{
		if (mlxs.ray_ang > 0 && mlxs.ray_ang <= M_PI)
			x_offset = fabs(fmod(mlxs.x_hit, mlxs.tile) - mlxs.tile);
		else
			x_offset = fmod(mlxs.x_hit, mlxs.tile);
	}
	x_offset *= (double)text.width / mlxs.tile;
	return (x_offset);
}

void	draw_wall(t_mlx mlxs, double x, double y_s, double h)
{
	double	y;
	double	y_wall;
	int		x_offset;
	int		y_offset;
	t_img	text;

	text = get_text_clr(mlxs);
	x_offset = get_x_offset(mlxs, text);
	y = 0;
	while (y < h && y < mlxs.height)
	{
		y_wall = y_s - (((double)mlxs.height / 2) - (h / 2));
		y_offset = y_wall * ((double)text.height / h);
		mlxs.wall_clr = mlx_get_color(text, x_offset, y_offset);
		my_mlx_pixel_put(&mlxs.img, x, y_s, mlxs.wall_clr);
		y++;
		y_s++;
	}
}

void	wall_projection(t_mlx mlxs, double dis, int x)
{
	double	wall_height;
	double	start_wall;

	get_wall_height(mlxs, dis, &start_wall, &wall_height);
	if (start_wall < 0)
		start_wall = 0;
	if (wall_height >= mlxs.height)
		draw_wall(mlxs, x, 0, wall_height);
	else
	{
		draw_wall(mlxs, x, start_wall, wall_height);
		draw_ceil(mlxs, x, 0, start_wall);
		draw_floor(mlxs, x, start_wall + wall_height, mlxs.height);
	}
}
