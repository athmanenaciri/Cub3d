/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:14:32 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/16 19:10:12 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"cub3D.h"
#include <math.h>


void	set_ray_ang(t_mlx *mlxs, t_rtrace *inter)
{
	inter->is_up = 0;
	inter->is_left = 0;
	if(mlxs->ray_ang >= 0 && mlxs->ray_ang <= (M_PI))
		inter->is_up = 1;
	if (mlxs->ray_ang >= (M_PI / 2) && mlxs->ray_ang <= ((3 * M_PI) / 2))
		inter->is_left = 1;
}

double	distance(t_mlx *mlxs, double x, double y)
{
	return(sqrt(pow(x - mlxs->x_p, 2) + pow(y - mlxs->y_p, 2)));
}


void	h_first_inserS(t_mlx *mlxs, t_rtrace *horizental)
{
	double addjacent;

	horizental->n_y = floor(mlxs->y_p / mlxs->tile) * mlxs->tile;
	if(horizental->is_up)
		horizental->n_y += mlxs->tile;
	addjacent = horizental->n_y - mlxs->y_p;
	horizental->n_x = mlxs->x_p + (addjacent / tan(mlxs->ray_ang));
	horizental->y_step = mlxs->tile;
	if(!horizental->is_up)
		horizental->y_step *= -1;
	horizental->x_step = fabs(horizental->y_step / tan(mlxs->ray_ang));
	if(horizental->is_left)
		horizental->x_step *= -1;
}

t_rtrace	h_interS(t_mlx *mlxs)
{
	t_rtrace horizental;
	int		moins;
	double x;
	double y;
	set_ray_ang(mlxs, &horizental);
	h_first_inserS(mlxs, &horizental);
	y = horizental.n_y;
	x = horizental.n_x;

	moins = 0;
	if(!horizental.is_up)
		moins = 1;
	while(x >= 0 && x / mlxs->tile < mlxs->map.map_width && y >= 0 && y / mlxs->tile < mlxs->map.map_height)
	{
		if (ft_strchr(mlxs->map.lines[((int)y / mlxs->tile) - moins][(int)x / mlxs->tile], "1 "))
		{
			horizental.n_x = x;
			horizental.n_y = y;
			break;
		}
		x += horizental.x_step;
		y += horizental.y_step;
	}
	horizental.dis = distance(mlxs, x, y);
	return(horizental);
}

void	v_first_inserS(t_mlx *mlxs, t_rtrace *vertical)
{
	double opposite;

	vertical->n_x = floor(mlxs->x_p / mlxs->tile) * mlxs->tile;
	if(!vertical->is_left)
		vertical->n_x += mlxs->tile;
	opposite = vertical->n_x - mlxs->x_p;
	vertical->n_y = mlxs->y_p + (opposite * tan(mlxs->ray_ang));
	vertical->x_step = mlxs->tile;
	if(vertical->is_left)
		vertical->x_step *= -1;
	vertical->y_step = fabs(tan(mlxs->ray_ang) * vertical->y_step);
	if(!vertical->is_up)
		vertical->y_step *= -1;
}


t_rtrace	v_interS(t_mlx	*mlxs)
{
	t_rtrace vertical;
	double x;
	double y;
	int		moins;


	set_ray_ang(mlxs, &vertical);
	v_first_inserS(mlxs, &vertical);

	y = vertical.n_y;
	x = vertical.n_x;
	moins = 0;
	if(vertical.is_left)
		moins = 1;
	while(x >= 0 && x / mlxs->tile < mlxs->map.map_width && y >= 0 && y / mlxs->tile < mlxs->map.map_height)
	{
		if (ft_strchr(mlxs->map.lines[(int)y / mlxs->tile][((int)x / mlxs->tile) - moins], "1 "))
		{
			vertical.n_x = x;
			vertical.n_y = y;
			break;
		}
		x += vertical.x_step;
		y += vertical.y_step;
	}
	vertical.dis = distance(mlxs, x, y);
	return(vertical);
}
void	cast_rays2(t_mlx *mlxs, int col)
{
	t_rtrace hor;
	t_rtrace ver;

	hor = h_interS(mlxs);
	ver = v_interS(mlxs);

	if (ver.dis < hor.dis)
	{
		mlxs->v = 1;
		mlxs->x_hit = ver.n_x;
		mlxs->y_hit = ver.n_y;
		wall_projection(*mlxs, ver.dis, col);
	}
	else
	{
		mlxs->v = 0;
		mlxs->x_hit = hor.n_x;
		mlxs->y_hit = hor.n_y;
		wall_projection(*mlxs, hor.dis, col);
	}
}

