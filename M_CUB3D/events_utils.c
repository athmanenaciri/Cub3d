/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:28:03 by okrich            #+#    #+#             */
/*   Updated: 2023/06/19 21:37:52 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_exit(t_mlx *mlxs)
{
	destroy_mlx(mlxs, 1, 1);
	exit(1);
	return (0);
}

int	move_player(int key, t_mlx *mlxs)
{
	mlxs->keys.event = 1;
	if (key == 53)
		ft_exit(mlxs);
	if (key == 123)
		mlxs->keys.r_left = 1;
	else if (key == 124)
		mlxs->keys.r_right = 1;
	else if (key == 0)
		mlxs->keys.a = 1;
	else if (key == 1)
		mlxs->keys.s = 1;
	else if (key == 2)
		mlxs->keys.d = 1;
	else if (key == 13)
		mlxs->keys.w = 1;
	else
		mlxs->keys.event = 0;
	return (0);
}

int	relase(int key, t_mlx *mlxs)
{
	int	all_is_relaised;

	if (key == 123)
		mlxs->keys.r_left = 0;
	else if (key == 124)
		mlxs->keys.r_right = 0;
	else if (key == 0)
		mlxs->keys.a = 0;
	else if (key == 1)
		mlxs->keys.s = 0;
	else if (key == 2)
		mlxs->keys.d = 0;
	else if (key == 13)
		mlxs->keys.w = 0;
	all_is_relaised = mlxs->keys.r_left | mlxs->keys.r_right | mlxs->keys.a;
	all_is_relaised |= mlxs->keys.w | mlxs->keys.d | mlxs->keys.s;
	if (all_is_relaised == 0)
		mlxs->keys.event = 0;
	return (0);
}
