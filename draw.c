/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:09:49 by okrich            #+#    #+#             */
/*   Updated: 2023/06/12 20:25:00 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	draw_line(t_mlx mlxs, double x1, double y1, double x2, double y2, int color)// NOTE : VALID but : reduce num of args
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
	// mlxs.ray_ang -= to_rad(180);
	// double faux = mlxs.ray_ang - mlxs.p_ang;
	while (col < mlxs.width)
	{
		is_left = 0;
		is_up = 0;
		mlxs.ray_ang = normalize_ang(mlxs.ray_ang);
		// faux = normalize_ang(faux);
		// printf("f_ang : %f cos : %f sin : %f tan : %f\n",mlxs.ray_ang * 180 / M_PI, cos(mlxs.ray_ang), sin(mlxs.ray_ang), tan(mlxs.ray_ang));
		// printf("v_ang : %f cos : %f sin : %f tan : %f\n",(faux) * 180 / M_PI, cos(faux), sin(faux), tan(faux));
		// faux += incr;
		// printf("ray_ang : %f\n",mlxs.ray_ang * 180 / M_PI);
		if (mlxs.ray_ang > 0 && mlxs.ray_ang <= M_PI)
			is_up = 1;
		if (mlxs.ray_ang >= M_PI / 2 && mlxs.ray_ang <= (3 *M_PI) / 2)
			is_left = 1;
		// printf("ray_ang : %f p_ang : %f \n",mlxs.ray_ang * 180 / M_PI, mlxs.p_ang * 180 / M_PI);
		cast_rays(&mlxs, col, is_up, is_left);
		col++;
		mlxs.ray_ang += incr;
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
	draw_line(mlxs, x, y, x + cos(mlxs.p_ang) * mlxs.mini_tile, y + sin(mlxs.p_ang) * mlxs.mini_tile, 0xff0000);
}

void	draw_cub(t_mlx mlxs, int x, int y, int color)
{
	double xx;
	double yy;
	double yi;
	double	mini_tile;

	xx = 0;
	yi = y;
	mini_tile = mlxs.mini_tile;
	while (xx < mini_tile && x < mlxs.width)
	{
		yy = 0;
		y = yi;
		while (yy < mini_tile && y < mlxs.height)
		{
			my_mlx_pixel_put(&mlxs.img, x, y, color);
			yy++;
			y++;
		}
		x++;
		xx++;
	}
}

void	draw_mini_map(t_mlx mlxs)
{
	int	x = 0;
	int	y = 0;
	int	xi = (mlxs.x_p/ mlxs.tile) - 5;
	int	yi = (mlxs.y_p / mlxs.tile) - 2;
	int	xf = (mlxs.x_p / mlxs.tile) + 5;
	int	yf = (mlxs.y_p / mlxs.tile) + 2;

	int	tmp_y = yi;
	while (xi < xf)
	{
		yi = tmp_y;
		y = 0;
		while (yi < yf)
		{
			if (xi < 0 || yi < 0 || xi >= mlxs.map.map_width || yi >= mlxs.map.map_height) 
				draw_cub(mlxs, x, y, 0x888080);
			else if (mlxs.map.lines[yi][xi] == '1')
				draw_cub(mlxs, x, y, 0x888080);
			else if (mlxs.map.lines[yi][xi] == '0')
				draw_cub(mlxs, x, y, 0xffffff);
			y += mlxs.mini_tile;
			yi++;
		}
		x += mlxs.mini_tile;
		xi++;
	}
	double xp =  (double)x / 2;//xf * mlxs.mini_tile; //(mlxs.x_p / mlxs.tile) + (10 * mlxs.mini_tile); 
	double yp =  (double)y / 2;//yf * mlxs.mini_tile; //(mlxs.x_p / mlxs.tile) + (10 * mlxs.mini_tile);
	// printf("xp : %f yp = %f\n",xp , yp);
	draw_cercle(mlxs, xp, yp, 2);

}

void	render(t_mlx mlxs)
{
	//draw_rays(mlxs);
	draw_rays2(mlxs);
	draw_mini_map(mlxs);
	mlx_put_image_to_window(mlxs.mlx, mlxs.mlx_win, mlxs.img.img, 0, 0);
}
