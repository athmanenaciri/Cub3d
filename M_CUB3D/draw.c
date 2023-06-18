/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:09:49 by okrich            #+#    #+#             */
/*   Updated: 2023/06/16 19:59:04 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

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
		// cast_rays2(&mlxs, col);
 		col++;
 		mlxs.ray_ang += incr;
 	}
}

void	render(t_mlx mlxs)
{
	draw_rays(mlxs);
	mlx_put_image_to_window(mlxs.mlx, mlxs.mlx_win, mlxs.img.img, 0, 0);
}
