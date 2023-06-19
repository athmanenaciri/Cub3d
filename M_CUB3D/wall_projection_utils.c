/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:27:53 by okrich            #+#    #+#             */
/*   Updated: 2023/06/19 10:39:52 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor(t_mlx mlxs, double x, double y, double h)
{
	while (y < h)
	{
		my_mlx_pixel_put(&mlxs.img, x, y, mlxs.map.floor_hex);
		y++;
	}
}

void	draw_ceil(t_mlx mlxs, double x, double y, double h)
{
	while (y < h)
	{
		my_mlx_pixel_put(&mlxs.img, x, y, mlxs.map.ceil_hex);
		y++;
	}
}

void	get_wall_height(t_mlx mlxs, double dis, double *yi, double *height)
{
	double	dis_plan;
	double	corr_dis;
	double	half_width;
	double	wall_height;

	corr_dis = dis * cos(mlxs.ray_ang - mlxs.p_ang);
	dis = corr_dis;
	half_width = (double)mlxs.width / 2;
	dis_plan = half_width / tan(to_rad(FOV / 2));
	wall_height = (mlxs.tile / dis) * dis_plan;
	*yi = ((double)mlxs.height / 2) - (wall_height / 2);
	*height = wall_height;
}
