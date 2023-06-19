/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:09:49 by okrich            #+#    #+#             */
/*   Updated: 2023/06/19 13:38:19 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_rays(t_mlx	mlxs)
{
	int		col;
	double	incr;
	int		is_up;
	int		is_left;

	col = 0;
	incr = to_rad(FOV) / mlxs.width;
	mlxs.ray_ang = mlxs.p_ang - (to_rad(FOV) / 2);
	while (col < mlxs.width)
	{
		is_left = 0;
		is_up = 0;
		mlxs.ray_ang = normalize_ang(mlxs.ray_ang);
		if (mlxs.ray_ang > 0 && mlxs.ray_ang <= M_PI)
			is_up = 1;
		if (mlxs.ray_ang >= M_PI / 2 && mlxs.ray_ang <= (3 * M_PI) / 2)
			is_left = 1;
		cast_rays(&mlxs, col, is_up, is_left);
		col++;
		mlxs.ray_ang += incr;
	}
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

int	is_outside_map(t_mlx mlxs, double xi, double yi)
{
	xi /= mlxs.tile;
	yi /= mlxs.tile;
	if (xi < 0 || xi >= mlxs.map.map_width
		|| yi < 0 || yi >= mlxs.map.map_height)
		return (1);
	return (0);
}

void	draw_mini_map(t_mlx mlxs, double xi, double yi, int center)
{
	double	tmp_y;
	int		x;
	int		y;

	tmp_y = yi;
	x = 0;
	while (++xi < mlxs.x_p + (2 * mlxs.tile))
	{
		y = -1;
		yi = tmp_y - 1;
		while (++yi < mlxs.y_p + (2 * mlxs.tile))
		{
			if (check_cercle(mlxs, center, x, ++y))
			{
				if (is_outside_map(mlxs, xi, yi))
					my_mlx_pixel_put(&mlxs.img, x, y, 0x000000);
				else if (mlxs.map.lines[(int)(yi / mlxs.tile)][(int)(xi
						/ mlxs.tile)] == '1')
					my_mlx_pixel_put(&mlxs.img, x, y, 0x888080);
				else
					my_mlx_pixel_put(&mlxs.img, x, y, 0xffffff);
			}
		}
		x++;
	}
}

void	render(t_mlx mlxs)
{
	double	x_minimap;
	double	y_minimap;

	x_minimap = mlxs.x_p - (2 * mlxs.tile);
	y_minimap = mlxs.y_p - (2 * mlxs.tile);
	draw_rays(mlxs);
	draw_mini_map(mlxs, x_minimap - 1, y_minimap, 2 * mlxs.tile);
	draw_cercle(mlxs, 2 * mlxs.tile, 2 * mlxs.tile, 10);
	mlx_put_image_to_window(mlxs.mlx, mlxs.mlx_win, mlxs.img.img, 0, 0);
}
