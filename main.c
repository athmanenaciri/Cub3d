#include "cub3D.h"
#include "minilibx_mms_20200219/mlx.h"

void b()
{
	system("leaks cub3d");
}

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		p_err("open : failed\n", 1);
	return (fd);
}

int	main(int ac, char **av)
{
	t_mlx	mlxs;
	t_map	map;

	// atexit(b);
	if (ac != 2)
		p_err("Number of arguments\n", 1);

	map = initialize_t_map();
	parse_map(av[1], &map);
	if_map_closed(ft_open(av[1]), &map);

	mlxs = initialize_t_mlx(map);
	mlxs.mlx = mlx_init();
	if (!mlxs.mlx)
		p_err("mlx_init Failed\n", 1);
	mlxs.mlx_win = mlx_new_window(mlxs.mlx, mlxs.width, mlxs.height, "Cub3d");
	if (!mlxs.mlx_win)
		p_err("mlx_new_window Failed\n", 1);
	mlxs.img.img = mlx_new_image(mlxs.mlx, mlxs.width, mlxs.height);
	if (!mlxs.img.img)
		return (mlx_destroy_window(mlxs.mlx, mlxs.mlx_win), p_err("mlx_init Failed\n", 1), 1);
	mlxs.text = init_text(map, mlxs.mlx);

	get_data_img(&mlxs.img);

	find_player(&mlxs);
	render(mlxs);
	
	mlx_loop_hook(mlxs.mlx, ft_key_hook, &mlxs);
	mlx_hook(mlxs.mlx_win, 2, 0, move_player, &mlxs);
	mlx_hook(mlxs.mlx_win, 3, 0, relase, &mlxs);

	mlx_hook(mlxs.mlx_win, 6, 0, mouse_move, &mlxs);
	
	mlx_hook(mlxs.mlx_win, 17, 0, ft_exit, &mlxs);
	mlx_loop(mlxs.mlx);
}
