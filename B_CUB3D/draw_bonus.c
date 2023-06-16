// #include "cub3D_bonus.h"
//
// double to_rad(double degree)
// {
// 	return (degree * M_PI / 180);
// }
//
//  void	draw_rays(t_mlx mlxs)
//  {
//  	int		col;
//  	double	incr;
//  	int		is_up;
//  	int		is_left;
//  	
//  	col = 0;
//  	incr = to_rad(FOV)	/ mlxs.width;
//  	mlxs.ray_ang = mlxs.p_ang - (to_rad(FOV) / 2); 
//  	while (col < mlxs.width)
//  	{
//  		is_left = 0;
//  		is_up = 0;
//  		mlxs.ray_ang = normalize_ang(mlxs.ray_ang);
//  		if (mlxs.ray_ang > 0 && mlxs.ray_ang <= M_PI)
//  			is_up = 1;
//  		if (mlxs.ray_ang >= M_PI / 2 && mlxs.ray_ang <= (3 *M_PI) / 2)
//  			is_left = 1;
//  		cast_rays(&mlxs, col, is_up, is_left);
//  		col++;
//  		mlxs.ray_ang += incr;
//  	}
// }
//
// void	render_bonus(t_mlx mlxs)
// {
// 	draw_rays(mlxs);
// 	draw_mini_map(mlxs);
// 	mlx_put_image_to_window(mlxs.mlx, mlxs.mlx_win, mlxs.img.img, 0, 0);
// }
//
