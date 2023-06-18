/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:15:41 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/18 19:16:35 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	normalize_ang(double ang)
{
	if (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	if (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

int	ft_exit(t_mlx *mlxs)
{
	mlx_destroy_image(mlxs->mlx, mlxs->img.img);
	mlx_destroy_window(mlxs->mlx, mlxs->mlx_win);
	exit(1);
	return (0);
}

void	handel_key(double *x, double *y, t_mlx *mlxs)
{
	if (mlxs->keys.r_left)
		mlxs->p_ang -= to_rad(2);
	if (mlxs->keys.r_right)
		mlxs->p_ang += to_rad(2);
	if (mlxs->keys.w)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang) * 10;
		*y = mlxs->y_p + sin(mlxs->p_ang) * 10;
	}
	if (mlxs->keys.s)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang) * -10;
		*y = mlxs->y_p + sin(mlxs->p_ang) * -10;
	}
	if (mlxs->keys.a)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang - to_rad(90)) * 10;
		*y = mlxs->y_p + sin(mlxs->p_ang - to_rad(90)) * 10;
	}
	if (mlxs->keys.d)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang + to_rad(90)) * 10;
		*y = mlxs->y_p + sin(mlxs->p_ang + to_rad(90)) * 10;
	}
}

int	move_player(int key, t_mlx *mlxs)
{
	mlxs->keys.event = 1;
	if (key == 53)
		ft_exit(mlxs);
	if (key == 123)
		mlxs->keys.r_left = 1;
	else if (key == 124)
		mlxs->keys.r_right = 1;
	else if (key == 0)
		mlxs->keys.a = 1;
	else if (key == 1)
		mlxs->keys.s = 1;
	else if (key == 2)
		mlxs->keys.d = 1;
	else if (key == 13)
		mlxs->keys.w = 1;
	else
		mlxs->keys.event = 0;
	return (0);
}

int	relase(int key, t_mlx *mlxs)
{
	int	all_is_relaised;

	if (key == 123)
		mlxs->keys.r_left = 0;
	else if (key == 124)
		mlxs->keys.r_right = 0;
	else if (key == 0)
		mlxs->keys.a = 0;
	else if (key == 1)
		mlxs->keys.s = 0;
	else if (key == 2)
		mlxs->keys.d = 0;
	else if (key == 13)
		mlxs->keys.w = 0;
	all_is_relaised = mlxs->keys.r_left | mlxs->keys.r_right | mlxs->keys.a;
	all_is_relaised |= mlxs->keys.w | mlxs->keys.d | mlxs->keys.s;
	if (all_is_relaised == 0)
		mlxs->keys.event = 0;
	return (0);
}

int	ft_key_hook(t_mlx *mlxs)
{
	double	x;
	double	y;

	if (mlxs->keys.event)
	{
		handel_key(&x, &y, mlxs);
		if (x < 0 || y < 0 || x / mlxs->tile >= mlxs->map.map_width
			|| y / mlxs->tile >= mlxs->map.map_height)
			return (1);
		if (mlxs->map.lines[(int)(y / mlxs->tile)][(int)x / mlxs->tile] != '1')
		{
			mlxs->x_p = x;
			mlxs->y_p = y;
		}
		mlx_destroy_image(mlxs->mlx, mlxs->img.img);
		mlxs->img.img = mlx_new_image(mlxs->mlx, mlxs->width, mlxs->height);
		get_data_img(&mlxs->img);
		mlx_clear_window(mlxs->mlx, mlxs->mlx_win);
		render(*mlxs);
	}
	return (1);
}
