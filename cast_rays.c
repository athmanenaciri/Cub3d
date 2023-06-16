/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:14:21 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/13 01:14:28 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	find_horz_itc(t_mlx *mlxs, t_rtrace *ray_trace)
{
	double	tan_ang;

	tan_ang = tan(mlxs->ray_ang);

	ray_trace->n_y = floor(mlxs->y_p / mlxs->tile) * mlxs->tile;
	if (ray_trace->is_up)
		ray_trace->n_y += mlxs->tile;	

	ray_trace->n_x = mlxs->x_p + (ray_trace->n_y - mlxs->y_p) / tan_ang;
	// if (ray_trace->n_x < 0) 
	// 	printf("n_x : %f\n",ray_trace->n_x);

	ray_trace->y_step = mlxs->tile;
	if (!ray_trace->is_up)
		ray_trace->y_step *= -1;
	ray_trace->x_step = fabs(mlxs->tile / tan_ang);
	if (ray_trace->is_left)
		ray_trace->x_step *= -1;
}

void	find_ver_itc(t_mlx *mlxs, t_rtrace *ray_trace)
{
	double	tan_ang;

	tan_ang = tan(mlxs->ray_ang);
	ray_trace->n_x = floor(mlxs->x_p / mlxs->tile) * mlxs->tile;
	if (!ray_trace->is_left)
		ray_trace->n_x += mlxs->tile;	

	ray_trace->n_y = mlxs->y_p + (ray_trace->n_x - mlxs->x_p) * tan_ang;
	// if (ray_trace->n_y < 0)
	// {
	// 	printf("y_p : %f opp : %f\n", mlxs->y_p, (ray_trace->n_x - mlxs->x_p) * tan_ang);
	// }

	ray_trace->x_step = mlxs->tile;
	if (ray_trace->is_left)
		ray_trace->x_step *= -1;
	ray_trace->y_step = fabs(mlxs->tile * tan_ang);
	if(!ray_trace->is_up)
		ray_trace->y_step *= -1;
}

double calcul_distance(t_mlx mlxs, t_rtrace ray)
{
	double d;
	double dx;
	double dy;

	dx = pow(ray.n_x - mlxs.x_p, 2);
	dy = pow(ray.n_y - mlxs.y_p, 2);
	d = sqrt(dx + dy);
	return (d);
}

void	check_horiztl(t_mlx *mlxs, t_rtrace *ray)
{
	double	x;
	double	y;
	int	moins;

	moins = 0;
	find_horz_itc(mlxs, ray);
	x = ray->n_x;
	y = ray->n_y;
	if (!ray->is_up)
		moins = 1;
	while (x >= 0 && x / mlxs->tile < mlxs->map.map_width && y >= 0 && y / mlxs->tile < mlxs->map.map_height)
	{
		if (ft_strchr(mlxs->map.lines[((int)y/mlxs->tile) - moins][(int)x/mlxs->tile] , "1 "))
			break ;
		x += ray->x_step;
		y += ray->y_step;
	}
	ray->n_x = x;
	ray->n_y = y;
	ray->dis = calcul_distance(*mlxs, *ray);
}

void	check_verticl(t_mlx *mlxs, t_rtrace *ray)
{
	double	x;
	double	y;
	int		moins;

	moins = 0;
	find_ver_itc(mlxs, ray);
	x = ray->n_x;
	y = ray->n_y;
	if (ray->is_left)
		moins = 1;
	while (x >= 0 && x  / mlxs->tile< mlxs->map.map_width && y >= 0 && y / mlxs->tile < mlxs->map.map_height)
	{
		if (ft_strchr(mlxs->map.lines[((int)y/mlxs->tile)][(int)x/mlxs->tile - moins] , "1 "))
			break ;
		x += ray->x_step;
		y += ray->y_step;
	}
	ray->n_x = x;
	ray->n_y = y;
	ray->dis = calcul_distance(*mlxs, *ray);
}

void	cast_rays(t_mlx *mlxs, int col, int is_up, int is_left)
{
	t_rtrace 	ver_ray;
	t_rtrace	hor_ray;
	
	hor_ray.is_up = is_up;
	hor_ray.is_left = is_left;
	ver_ray.is_left = is_left;
	ver_ray.is_up = is_up;
	check_horiztl(mlxs, &hor_ray);
	check_verticl(mlxs, &ver_ray);
	if (ver_ray.dis < hor_ray.dis)
	{
		mlxs->v = 1;
		mlxs->x_hit = ver_ray.n_x;
		mlxs->y_hit = ver_ray.n_y;
		wall_projection(*mlxs, ver_ray.dis, col);
	}
	else
	{
		mlxs->v = 0;
		mlxs->x_hit = hor_ray.n_x;
		mlxs->y_hit = hor_ray.n_y;
		wall_projection(*mlxs, hor_ray.dis, col);
	}
}
