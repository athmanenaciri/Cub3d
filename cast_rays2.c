#include"cub3D.h"
#include <math.h>

void	h_first_inserS(t_mlx *mlxs, t_rtrace *horizental)
{
	int addjacent;

	horizental->n_y = floor(mlxs->y_p / mlxs->tile) * mlxs->tile;
	if(horizental->is_up)
		horizental->n_y += mlxs->tile;
	addjacent = horizental->n_y - mlxs->y_p;
	horizental->n_x = mlxs->x_p + (addjacent / tan(mlxs->ray_ang));
	horizental->y_step = mlxs->tile;
	if(!horizental->is_up)
		horizental->y_step *= mlxs->tile;
	horizental->x_step = fabs(horizental->y_step / tan(mlxs->ray_ang));
	if(horizental->is_left)
		horizental->x_step *= -1;
}

double	distance(t_mlx *mlxs, double x, double y)
{
	return(sqrt(pow(x - mlxs->x_p, 2) + pow(y - mlxs->y_p, 2)));
}

double	h_interS(t_mlx *mlxs)
{
	t_rtrace horizental;
	double x;
	double y;
	double dis;

	dis = 0;
	h_first_inserS(mlxs, &horizental);

	y = horizental.n_y;
	while(x >= 0 && x <= mlxs->width && y >= 0 && y <= mlxs->height)
	{
		x = x / mlxs->tile;
		y = y / mlxs->tile;
		if(horizental.is_up)
			y -= 1;
		if (!ft_strchr(mlxs->map.lines[(int)y][(int)x], "1 "))
		{	
			distance(mlxs, x *mlxs->tile, y * mlxs->tile);
			break;
		}
		x = (x * mlxs->tile) + horizental.x_step;
		y = (y * mlxs->tile) + horizental.y_step;
	}
}

void	v_first_inserS(t_mlx *mlxs, t_rtrace *vertical)
{
	int addjacent;

	vertical->n_x = floor(mlxs->x_p / mlxs->tile) * mlxs->tile;
	if(vertical->is_left)
		vertical->n_x += mlxs->tile;
	addjacent = vertical->n_x - mlxs->x_p;
	vertical->n_y = mlxs->y_p + (addjacent * tan(mlxs->ray_ang));
	vertical->x_step = mlxs->tile;
	if(!vertical->is_up)
		vertical->y_step *= mlxs->tile;
	vertical->x_step = fabs(vertical->y_step / tan(mlxs->ray_ang));
	if(vertical->is_left)
		vertical->x_step *= -1;
}


double	v_interS(t_mlx	*mlxs)
{
	t_rtrace vertical;
	double x;
	double y;
	double dis;

	dis = 0;

	v_first_inserS(mlxs, &vertical);
}
void	set_ray_ang(t_mlx *mlxs, t_rtrace *hor, t_rtrace *ver)
{
	if(mlxs->ray_ang >= 0 && mlxs->ray_ang <= (M_PI))
	{
		hor->is_up = 1;
		ver->is_up = 1;
	}
	else if (mlxs->ray_ang >= (M_PI / 2) && mlxs->ray_ang <= ((3 * M_PI) / 2))
	{
		hor->is_left = 0;
		ver->is_left = 0;
	}
}
void	cast_rays2(t_mlx *mlxs, int x)
{
	t_rtrace hor;
	t_rtrace ver;

	set_ray_ang(mlxs, &hor, &ver)
	hor = h_interS(mlxs);
	ver = v_interS(mlxs);
	
		// hor ->
	//       x and y first inter
	//       x and y step
	// ver
	//       x and y first inter
	//       x and y step
}


