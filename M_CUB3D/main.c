/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:39:06 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/20 16:07:16 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		p_err("open : failed\n", 1);
	return (fd);
}

void	destroy_mlx(t_mlx *mlxs, int img, int win)
{
	if (img)
		mlx_destroy_image(mlxs->mlx, mlxs->img.img);
	mlx_destroy_image(mlxs->mlx, mlxs->text.no_text.img);
	mlx_destroy_image(mlxs->mlx, mlxs->text.so_text.img);
	mlx_destroy_image(mlxs->mlx, mlxs->text.ea_text.img);
	mlx_destroy_image(mlxs->mlx, mlxs->text.we_text.img);
	if (win)
		mlx_destroy_window(mlxs->mlx, mlxs->mlx_win);
}

int	init_mlx(t_mlx	*mlxs, t_map map)
{
	*mlxs = initialize_t_mlx(map);
	mlxs->mlx = mlx_init();
	if (!mlxs->mlx)
		p_err("mlx_init Failed\n", 1);
	mlxs->text = init_text(map, mlxs->mlx);
	mlxs->mlx_win = mlx_new_window(mlxs->mlx, mlxs->width, mlxs->height,
			"Cub3d");
	if (!mlxs->mlx_win)
		return (destroy_mlx(mlxs, 0, 0), p_err("mlx_new_window Failed\n", 1), 1);
	mlxs->img.img = mlx_new_image(mlxs->mlx, mlxs->width, mlxs->height);
	if (!mlxs->img.img)
		return (destroy_mlx(mlxs, 0, 1), p_err("mlx_init Failed\n", 1), 1);
	get_data_img(&mlxs->img);
	find_player(mlxs);
	render(*mlxs);
	return (1);
}

int	main(int ac, char **av)
{
	t_mlx	mlxs;
	t_map	map;

	if (ac != 2)
		p_err("Number of arguments\n", 1);
	map = initialize_t_map();
	parse_map(av[1], &map);
	if_map_closed(ft_open(av[1]), &map);
	init_mlx(&mlxs, map);
	mlx_loop_hook(mlxs.mlx, ft_key_hook, &mlxs);
	mlx_hook(mlxs.mlx_win, 2, 0, move_player, &mlxs);
	mlx_hook(mlxs.mlx_win, 3, 0, relase, &mlxs);
	mlx_hook(mlxs.mlx_win, 17, 0, ft_exit, &mlxs);
	mlx_loop(mlxs.mlx);
}
