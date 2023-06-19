/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:38:32 by okrich            #+#    #+#             */
/*   Updated: 2023/06/19 11:38:54 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

double	normalize_ang(double ang)
{
	if (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	if (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

double	to_rad(double degree)
{
	return (degree * M_PI / 180);
}
