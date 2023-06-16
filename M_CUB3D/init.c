#include "cub3D.h"
#include <stdlib.h>

double	set_ang(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	else if (c == 'S')
		return (M_PI / 2);
	else if (c == 'W')
		return (M_PI);
	else if (c == 'E')
		return (0);
	return (0);
}

void	find_player(t_mlx *mlxs)
{
	int		x;
	int		y;

	y = 0;
	while (y < mlxs->map.map_height)
	{
		x = 0;
		while (x < mlxs->map.map_width)
		{
			if (ft_strchr(mlxs->map.lines[y][x], "NSEW"))
			{
				mlxs->x_p = x * mlxs->tile;
				mlxs->y_p = y * mlxs->tile;
				mlxs->p_ang = set_ang(mlxs->map.lines[y][x]);
				mlxs->map.lines[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
	mlxs->x_p += (double)mlxs->tile / 2; 
	mlxs->y_p += (double)mlxs->tile / 2; 
}

t_mlx initialize_t_mlx(t_map map)
{
    t_mlx	mlx;

    mlx.x_p = 0;
    mlx.y_p = 0;
    mlx.p_ang = 0;
	mlx.map = map;
	mlx.tile = 64;
	mlx.height = 1024;
	mlx.width = 1024;
	mlx.keys.event = 0;
	mlx.keys.s = 0;
	mlx.keys.a = 0;
	mlx.keys.w = 0;
	mlx.keys.d = 0;
	mlx.keys.r_right = 0;
	mlx.keys.r_left = 0;
    return (mlx);
}

t_map initialize_t_map(void)
{
	t_map	map;

	map.lines = NULL;
	map.no_text = NULL;
	map.so_text = NULL;
	map.ea_text = NULL;
	map.we_text = NULL;
	map.map_height = 0;
	map.map_width = 0;
	map.map_skip = 0;
    return (map);
}

void	free_text(t_map map)
{
	free(map.no_text);
	free(map.so_text);
	free(map.we_text);
	free(map.ea_text);
}

t_textu init_text(t_map map, void *mlx)
{
	t_textu	textu;

	textu.no_text.img = mlx_xpm_file_to_image(mlx, map.no_text, &textu.no_text.width, &textu.no_text.height);
	if (!textu.no_text.img)
		return (p_err("convert xpm to img failed\n", 1), textu);
	get_data_img(&textu.no_text);
	textu.so_text.img = mlx_xpm_file_to_image(mlx, map.so_text, &textu.so_text.width, &textu.so_text.height);
	if (!textu.so_text.img)
		return (p_err("convert xpm to img failed\n", 1), textu);
	get_data_img(&textu.so_text);
	textu.we_text.img = mlx_xpm_file_to_image(mlx, map.we_text, &textu.we_text.width, &textu.we_text.height);
	if (!textu.we_text.img)
		return (p_err("convert xpm to img failed\n", 1), textu);
	get_data_img(&textu.we_text);
	textu.ea_text.img = mlx_xpm_file_to_image(mlx, map.ea_text, &textu.ea_text.width, &textu.ea_text.height);
	if (!textu.ea_text.img)
		return (p_err("convert xpm to img failed\n", 1), textu);
	get_data_img(&textu.ea_text);
	return (free_text(map), textu);
}
