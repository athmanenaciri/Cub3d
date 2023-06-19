/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:37:20 by okrich            #+#    #+#             */
/*   Updated: 2023/06/19 12:07:18 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	calcul_distance(t_mlx mlxs, t_rtrace ray)
{
	double	d;
	double	dx;
	double	dy;

	dx = pow(ray.n_x - mlxs.x_p, 2);
	dy = pow(ray.n_y - mlxs.y_p, 2);
	d = sqrt(dx + dy);
	return (d);
}

double	to_rad(double degree)
{
	return (degree * M_PI / 180);
}

void	draw_cercle(t_mlx mlxs, double x, double y, int r)
{
	double	xx;
	double	yy;
	double	dx;
	double	dy;
	double	d;

	yy = 0;
	xx = 0;
	while (xx < mlxs.width)
	{
		yy = 0;
		while (yy < mlxs.height)
		{
			dx = xx - x;
			dy = yy - y;
			d = sqrt(pow(dx, 2) + pow(dy, 2));
			if (d < r)
				my_mlx_pixel_put(&mlxs.img, xx, yy, 0xff0000);
			yy += 1;
		}
		xx += 1;
	}
}
