#include"cub3D.h"
#include <math.h>

double	set_ang(char c)
{
	if(c == 'N')
		return((3 *M_PI) /2);
	else if(c == 'S')
		return(M_PI / 2);
	else if(c == 'E')
		return(0);
	else
		return(M_PI);

}
void	find_player(t_mlx *mlxs)
{
	int x;
	int y;
	char store;

	y = 0;
	while(y < mlxs->map.map_height)
	{
		x = 0;
		while(x < mlxs->map.map_width)
		{

			if(!ft_strchr(mlxs->map.lines[y][x], "NESW"))
			{
				store = mlxs->map.lines[y][x];
				mlxs->map.lines[y][x] = '0';
				mlxs->x_p = (x * mlxs->tile) + ((double)mlxs->tile / 2);
				mlxs->y_p = (y * mlxs->tile) + ((double)mlxs->tile / 2);
				break;
			}
			x++;
		}
		y++;
	}
	mlxs->p_ang =  set_ang(store);
}

double	norm_ang(double ang)
{
	if(ang > (2 * M_PI))
		ang -= (2 * M_PI);
	if(ang < 0)
		ang += (2 * M_PI);
	return(ang);
}

void	draw_rays(t_mlx *mlxs)
{
	int i;
	double inc = to_rad(FOV) / mlxs->width;


	i = 0;
	mlxs->ray_ang = mlxs->p_ang - (to_rad(FOV) / 2);
	while(i < mlxs->width)
	{
		mlxs->ray_ang = norm_ang(mlxs->ray_ang);
		mlxs->ray_ang = norm_ang(mlxs->ray_ang);
		cast_rays2(mlxs, i);
		i++;
		mlxs->ray_ang += inc;
	}
}
