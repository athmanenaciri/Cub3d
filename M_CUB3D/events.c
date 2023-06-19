/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:15:41 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/19 11:30:24 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	ft_key_hook(t_mlx *mlxs)
{
	double	x;
	double	y;

	if (mlxs->keys.event)
	{
		handel_key(&x, &y, mlxs);
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
