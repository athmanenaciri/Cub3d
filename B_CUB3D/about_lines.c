/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:56:07 by okrich            #+#    #+#             */
/*   Updated: 2023/06/20 15:31:58 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	empty_line(char *line, int fd)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (free(line), 1);
	while (line[i])
	{
		if (line[i] == '\t')
			return (close(fd), free(line), p_err("unexpected code\n", 1), 0);
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
