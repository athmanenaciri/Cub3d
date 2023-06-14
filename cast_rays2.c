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
		horizental->y_step *= -1;
	horizental->x_step = fabs(horizental->y_step / tan(mlxs->ray_ang));
	if(horizental->is_left)
		horizental->x_step *= -1;
}

double	distance(t_mlx *mlxs, double x, double y)
{
	return(sqrt(pow(x - mlxs->x_p, 2) + pow(y - mlxs->y_p, 2)));
}

t_rtrace	h_interS(t_mlx *mlxs)
{
	t_rtrace horizental;
	double x;
	double y;
	double dis;

	dis = 0;
	h_first_inserS(mlxs, &horizental);
	y = horizental.n_y;
	x = horizental.n_x;

	if(horizental.is_up)
		y -= mlxs->tile;
	while(x >= 0 && x < mlxs->width && y >= 0 && y < mlxs->height)
	{
		x = x / mlxs->tile;
		y = y / mlxs->tile;
		if (!ft_strchr(mlxs->map.lines[(int)y][(int)x], "1 "))
			break;
		horizental.n_x = x * mlxs->tile;
		horizental.n_y = y * mlxs->tile;
		x = (x * mlxs->tile) + horizental.x_step;
		y = (y * mlxs->tile) + horizental.y_step;
	}
	horizental.dis = distance(mlxs, x *mlxs->tile, y * mlxs->tile);
	return(horizental);
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
	if(!vertical->is_left)
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
	double dis;

	dis = 0;

	v_first_inserS(mlxs, &vertical);

	y = vertical.n_y;
	x = vertical.n_x;
	if(vertical.is_left)
		x -= mlxs->tile;
	while(x >= 0 && x < mlxs->width && y >= 0 && y < mlxs->height)
	{
		x = x / mlxs->tile;
		y = y / mlxs->tile;
		if (!ft_strchr(mlxs->map.lines[(int)y][(int)x], "1 "))
			break;
		vertical.n_x = x * mlxs->tile;
		vertical.n_y = y * mlxs->tile;
		x = (x * mlxs->tile) + vertical.x_step;
		y = (y * mlxs->tile) + vertical.y_step;
	}
	vertical.dis = distance(mlxs, x *mlxs->tile, y * mlxs->tile);
	return(vertical);
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
void	cast_rays2(t_mlx *mlxs, int col)
{
	t_rtrace hor;
	t_rtrace ver;

	set_ray_ang(mlxs, &hor, &ver);

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
	
		// hor ->
	//       x and y first inter
	//       x and y step
	// ver
	//       x and y first inter
	//       x and y step
}


