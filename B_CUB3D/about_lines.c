/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:56:07 by okrich            #+#    #+#             */
/*   Updated: 2023/06/18 20:03:36 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (free(line), 1);
	while (line[i])
	{
		if (line[i] == '\t')
			return (free(line), p_err("Character not expected\n", 0), 0);
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (free(line), 1);
}

int	skip_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!ft_strchr(line[i], "01 NSWE"))
			return (0);
		i++;
	}
	return (1);
}
