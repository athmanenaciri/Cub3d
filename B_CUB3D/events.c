/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:04:08 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/19 20:49:38 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	handel_key(double *x, double *y, t_mlx *mlxs)
{
	if (mlxs->keys.r_left)
		mlxs->p_ang -= to_rad(6);
	if (mlxs->keys.r_right)
		mlxs->p_ang += to_rad(6);
	if (mlxs->keys.w)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang) * 15;
		*y = mlxs->y_p + sin(mlxs->p_ang) * 15;
	}
	if (mlxs->keys.s)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang) * -15;
		*y = mlxs->y_p + sin(mlxs->p_ang) * -15;
	}
	if (mlxs->keys.a)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang - to_rad(90)) * 15;
		*y = mlxs->y_p + sin(mlxs->p_ang - to_rad(90)) * 15;
	}
	if (mlxs->keys.d)
	{
		*x = mlxs->x_p + cos(mlxs->p_ang + to_rad(90)) * 15;
		*y = mlxs->y_p + sin(mlxs->p_ang + to_rad(90)) * 15;
	}
}

int	mouse_move(int x, int y, t_mlx *mlxs)
{
	if (y >= 0 && y < mlxs->height && x >= 0 && x < mlxs->width)
	{
		mlxs->keys.new_x_mouse = x;
		mlxs->keys.mouse_move = 1;
	}
	else
		mlxs->keys.mouse_move = 0;
	return (0);
}

void	chng_ang(t_mlx *mlxs)
{
	double	tier;

	tier = (double)mlxs->width / 3;
	if (mlxs->keys.x_mouse - tier > mlxs->keys.new_x_mouse)
		mlxs->p_ang -= to_rad(4);
	else if (mlxs->keys.x_mouse + tier < mlxs->keys.new_x_mouse)
		mlxs->p_ang += to_rad(4);
	else
		mlxs->keys.mouse_move = 0;
	mlxs->p_ang = normalize_ang(mlxs->p_ang);
}

int	wall_colision(t_mlx *mlxs, double x, double y)
{
	int	xi;
	int	yi;
	int	air;

	air = 5;
	xi = x - air;
	while (xi < x + air)
	{
		yi = y - air;
		while (yi < y + air)
		{
			if (x < 0 || x / mlxs->tile >= mlxs->map.map_width
				|| y < 0 || y / mlxs->tile >= mlxs->map.map_height)
			{
				yi++;
				continue ;
			}
			if (mlxs->map.lines[(int)(yi / mlxs->tile)][(int)xi / mlxs->tile]
				== '1')
				return (0);
			yi++;
		}
		xi++;
	}
	return (1);
}

int	ft_key_hook(t_mlx *mlxs)
{
	double	x;
	double	y;

	if (mlxs->keys.event || mlxs->keys.mouse_move)
	{
		if (mlxs->keys.event)
		{
			handel_key(&x, &y, mlxs);
			if (wall_colision(mlxs, x, y))
			{
				mlxs->x_p = x;
				mlxs->y_p = y;
			}
		}
		if (mlxs->keys.mouse_move)
			chng_ang(mlxs);
		mlx_destroy_image(mlxs->mlx, mlxs->img.img);
		mlxs->img.img = mlx_new_image(mlxs->mlx, mlxs->width, mlxs->height);
		if (!mlxs->img.img)
			return (destroy_mlx(mlxs, 0, 1), p_err("init image\n", 1), 1);
		get_data_img(&mlxs->img);
		mlx_clear_window(mlxs->mlx, mlxs->mlx_win);
		render(*mlxs);
	}
	return (1);
}
