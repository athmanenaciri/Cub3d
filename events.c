// #include "cub3D.h"
// #include "minilibx_mms_20200219/mlx.h"
// #include <stdio.h>
//
// double	normalize_ang(double ang)
// {
// 	if (ang >= 2 * M_PI)
// 		ang -= 2 * M_PI;
// 	if (ang < 0)
// 		ang += 2 * M_PI;
// 	return (ang);
// }
//
// int	ft_exit(t_mlx *mlxs)
// {
// 	mlx_destroy_image(mlxs->mlx, mlxs->img.img);
// 	mlx_destroy_window(mlxs->mlx, mlxs->mlx_win);
// 	exit(1);
// 	return (0);
// }
//
// void	handel_key(int key, double *x, double *y, t_mlx *mlxs)
// {
// 	if (key == 123)
// 		mlxs->p_ang += to_rad(-7);
// 	if (key == 124)
// 		mlxs->p_ang += to_rad(7);
// 	if (key == 13)
// 	{
// 		*x = mlxs->x_p + cos(mlxs->p_ang) * 10;
// 		*y = mlxs->y_p + sin(mlxs->p_ang) * 10;
// 	}
// 	if (key == 1)
// 	{
// 		*x = mlxs->x_p + cos(mlxs->p_ang) * -10;
// 		*y = mlxs->y_p + sin(mlxs->p_ang) * -10;
// 	}
// 	if (key == 0)
// 	{
// 		*x = mlxs->x_p + cos(mlxs->p_ang - to_rad(90)) * 10;
// 		*y = mlxs->y_p + sin(mlxs->p_ang - to_rad(90)) * 10;
// 	}
// 	if (key == 2)
// 	{
// 		*x = mlxs->x_p + cos(mlxs->p_ang + to_rad(90)) * 10;
// 		*y = mlxs->y_p + sin(mlxs->p_ang + to_rad(90)) * 10;
// 	}
// }
//
// int	move_player(int key, t_mlx *mlxs)
// {
// 	if (key == 53)
// 		ft_exit(mlxs);
// 	if (key == 123 || key == 124 || key == 13 || (key >= 0 && key <= 2))
// 	{
// 		mlxs->event = 0;
// 		mlxs->key = 1;
// 		mlxs->k_key = key;
// 	}
// 	else
// 		mlxs->key = 0;
// 	return (0);
// }
//
// int	relase(int key, t_mlx *mlxs)
// {
// 	if (key == 123 || key == 124 || key == 13 || (key >= 0 && key <= 2))
// 		mlxs->event = 1;
// 	return (0);
// }
//
// int	mouse_move(int x, int y, t_mlx *mlxs)
// {
// 	if (y >= 0 && y < mlxs->height && x >= 0 && x < mlxs->width)
// 	{
// 		mlxs->new_x_mouse = x;	
// 		mlxs->mouse_move = 1;
// 	}
// 	else
// 		mlxs->mouse_move = 0;
//
// 	return (0);
// }
//
// void	chng_ang(t_mlx *mlxs)
// {
// 	if (mlxs->x_mouse - 100> mlxs->new_x_mouse)
// 		mlxs->p_ang -= to_rad(4);
// 	else if(mlxs->x_mouse + 100< mlxs->new_x_mouse)
// 		mlxs->p_ang += to_rad(4);
// }
//
// // int	check_wall(t_mlx *mlxs, int x, int y)
// // {
// // 	if (mlxs->map.lines[y / mlxs->tile][x / mlxs->tile] != '1')
// // 		return (0);
// //
// // 	return (1);
// // }
//
// int	ft_key_hook(t_mlx *mlxs)
// {
// 	double	x;
// 	double	y;
//
// 	if ((mlxs->event == 0 && mlxs->key) || mlxs->mouse_move)
// 	{
// 		if (mlxs->key == 1 && mlxs->event == 0)
// 		{
// 			handel_key(mlxs->k_key, &x, &y, mlxs);
// 			if (mlxs->map.lines[(int)(y / mlxs->tile)][(int)x / mlxs->tile] != '1')
// 			{
// 				mlxs->x_p = x;
// 				mlxs->y_p = y;
// 			}
// 		}
// 		if (mlxs->mouse_move)
// 			chng_ang(mlxs);	
// 		mlxs->p_ang = normalize_ang(mlxs->p_ang);
// 		mlx_destroy_image(mlxs->mlx, mlxs->img.img);
// 		mlxs->img.img = mlx_new_image(mlxs->mlx, mlxs->width, mlxs->height);
// 		get_data_img(&mlxs->img);
// 		mlx_clear_window(mlxs->mlx, mlxs->mlx_win);
// 		render(*mlxs);
// 	}
// 	return (1);
// }
