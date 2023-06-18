/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:54:10 by okrich            #+#    #+#             */
/*   Updated: 2023/06/18 20:05:11 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	p_err(char *line, int f_exit)
{
	write(2, "Error\n", 6);
	write(2, line, ft_strlen(line));
	if (f_exit)
		exit(1);
}

int	ft_atoi(char *str)
{
	int	nb;	
	int	i;

	nb = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (p_err("Error in color value\n", 0), -1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		if (nb > 255 || nb < 0)
			return (p_err("Number is outside the range [0,255]\n", 0), -1);
		i++;
	}
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (p_err("Number should not be separed by ESP\n", 0), -1);
		i++;
	}
	return (nb);
}
