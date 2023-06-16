/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:09:49 by okrich            #+#    #+#             */
/*   Updated: 2023/06/15 19:33:54 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double to_rad(double degree)
{
	return (degree * M_PI / 180);
}

 void	draw_rays(t_mlx mlxs)
 {
 	int		col;
 	double	incr;
 	int		is_up;
 	int		is_left;
 	
 	col = 0;
 	incr = to_rad(FOV)	/ mlxs.width;
 	mlxs.ray_ang = mlxs.p_ang - (to_rad(FOV) / 2); 
 	while (col < mlxs.width)
 	{
 		is_left = 0;
 		is_up = 0;
 		mlxs.ray_ang = normalize_ang(mlxs.ray_ang);
 		if (mlxs.ray_ang > 0 && mlxs.ray_ang <= M_PI)
 			is_up = 1;
 		if (mlxs.ray_ang >= M_PI / 2 && mlxs.ray_ang <= (3 *M_PI) / 2)
 			is_left = 1;
 		cast_rays(&mlxs, col, is_up, is_left);
 		col++;
 		mlxs.ray_ang += incr;
 	}
}

void	draw_line(t_mlx mlxs, double x1, double y1, double x2, double y2, int color)
{
	float x, y, xi, yi;
	double dx, dy;
	int num_step, i;

	i = 0;
	x = x1;
	y = y1;
	dx = x2 - x;
	dy = y2 - y;
	num_step = fabs(dy);	
	if (fabs(dx) > fabs(dy))
		num_step = fabs(dx);
	xi = (float)dx / num_step;
	yi = (float)dy /num_step;
	while (i < num_step)
	{
		my_mlx_pixel_put(&mlxs.img, x, y, color);
		x += xi;	
		y += yi;
		i++;
	}
}

void	draw_cercle(t_mlx mlxs, double x, double y, int r) // NOTE : VALID
{
	double xx = 0;
	double yy = 0;
	double dx;
	double dy;
	double d;

	while (xx < mlxs.width)	
	{
		yy = 0;
		while (yy < mlxs.height)
		{
			dx = xx - x;
			dy = yy - y;
			d = sqrt(pow(dx,2) + pow(dy, 2));
			if (d < r)
				my_mlx_pixel_put(&mlxs.img, xx,yy,0xff0000);
			yy += 1;
		}
		xx += 1;
	}
	draw_line(mlxs, x, y, x + cos(mlxs.p_ang) * 20, y + sin(mlxs.p_ang) * 20, 0xff0000);
}

int	check_cercle(t_mlx mlxs, int center, double x, double y)
{
	double	dis;
	double	r;

	r = 2 * mlxs.tile;
	dis = sqrt(pow(center - x, 2) + pow(center - y, 2));
	if (dis < r)
		return (1);
	return (0);
}

void	draw_mini_map(t_mlx mlxs)
{
	double	xi;
	double	yi;
	double	tmp_y;
	int		x;
	int		y;
	int		center = 2 * mlxs.tile;

	xi = mlxs.x_p - (2 * mlxs.tile);
	yi = mlxs.y_p - (2 * mlxs.tile);
	tmp_y = yi;
	x = 0;

	while (xi < mlxs.x_p + (2 * mlxs.tile))
	{
		y = 0;
		yi = tmp_y;
		while (yi < mlxs.y_p + (2 * mlxs.tile))
		{
			if (check_cercle(mlxs, center, x, y))
			{
				if (xi < 0 || (xi / mlxs.tile >= mlxs.map.map_width) || yi < 0 || (yi / mlxs.tile) >= mlxs.map.map_height)
					my_mlx_pixel_put(&mlxs.img, x, y, 0x000000);
				else if (mlxs.map.lines[(int)(yi / mlxs.tile)][(int)(xi / mlxs.tile)] == '1')
					my_mlx_pixel_put(&mlxs.img, x, y, 0x888080);
				else
					my_mlx_pixel_put(&mlxs.img, x, y, 0xffffff);
			}
			yi++;
			y++;
		}
		x++;
		xi++;
	}
	draw_cercle(mlxs, 2 * mlxs.tile, 2 * mlxs.tile, 3);

}

void	render(t_mlx mlxs)
{
	draw_rays(mlxs);
	draw_mini_map(mlxs);
	mlx_put_image_to_window(mlxs.mlx, mlxs.mlx_win, mlxs.img.img, 0, 0);
}
