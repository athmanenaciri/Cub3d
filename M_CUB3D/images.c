/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:21:49 by okrich            #+#    #+#             */
/*   Updated: 2023/06/19 16:07:29 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_data_img(t_img	*img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	void	*dst;

	dst = img->addr + (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(int *)dst = color;
}

int	mlx_get_color(t_img img, int x, int y)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(int *)dst);
}

void	err_textures(t_textu textu, int nb, void *mlx)
{
	mlx_destroy_image(mlx, textu.no_text);
	nb--;
	if (nb)
		mlx_destroy_image(mlx, textu.so_text);
	nb--;
	if (nb)
		mlx_destroy_image(mlx, textu.we_text);
	nb--;
	if (nb)
		mlx_destroy_image(mlx, textu.ea_text);
	free(mlx);
	p_err("convert mlx_xpm_file_to_image failed\n", 1);
}

t_textu	init_text(t_map map, void *mlx)
{
	t_textu	textu;

	textu.no_text.img = mlx_xpm_file_to_image(mlx, map.no_text,
			&textu.no_text.width, &textu.no_text.height);
	if (!textu.no_text.img)
		err_textures(textu, 1, mlx);
	get_data_img(&textu.no_text);
	textu.so_text.img = mlx_xpm_file_to_image(mlx, map.so_text,
			&textu.so_text.width, &textu.so_text.height);
	if (!textu.so_text.img)
		err_textures(textu, 2, mlx);
	get_data_img(&textu.so_text);
	textu.we_text.img = mlx_xpm_file_to_image(mlx, map.we_text,
			&textu.we_text.width, &textu.we_text.height);
	if (!textu.we_text.img)
		err_textures(textu, 3, mlx);
	get_data_img(&textu.we_text);
	textu.ea_text.img = mlx_xpm_file_to_image(mlx, map.ea_text,
			&textu.ea_text.width, &textu.ea_text.height);
	if (!textu.ea_text.img)
		err_textures(textu, 4, mlx);
	get_data_img(&textu.ea_text);
	return (free_text(map), textu);
}
