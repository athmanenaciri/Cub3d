/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:40:33 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/18 20:07:39 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	map_sides(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->lines[i][j])
		if (ft_strchr(map->lines[i][j++], "0NSWE"))
			return (1);
	j = 0;
	while (map->lines[map->map_height - 1][j])
		if (ft_strchr(map->lines[map->map_height - 1][j++], "0NSWE"))
			return (1);
	j = 0;
	while (j < map->map_height && map->lines[j][0])
		if (ft_strchr(map->lines[j++][0], "0NSWE"))
			return (1);
	j = -1;
	while (++j < map->map_height && map->lines[j][ft_strlen(map->lines[j]) - 1])
		if (ft_strchr(map->lines[j][ft_strlen(map->lines[j]) - 1], "0NSWE"))
			return (1);
	return (0);
}

char	*change_spaces(char *line, int width)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc(sizeof(char) * width + 1);
	if (!new_line)
		p_err("Allocation failed\n", 1);
	new_line[width] = '\0';
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
		new_line[i++] = ' ';
	free(line);
	return (new_line);
}

void	replace_spaces(t_map *map)
{
	int	i;

	i = -1;
	while (map->lines[++i])
		map->lines[i] = change_spaces(map->lines[i], map->map_width);
}

int	check_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->map_height - 1)
	{
		j = 1;
		while (j < map->map_width - 1)
		{
			if (ft_strchr(map->lines[i][j], "0SNWE"))
			{
				if (ft_strchr(map->lines[i - 1][j], " "))
					return (p_err("Map must be surrounded by wall\n", 1), 1);
				if (ft_strchr(map->lines[i + 1][j], " "))
					return (p_err("Map must be surrounded by wall\n", 1), 1);
				if (ft_strchr(map->lines[i][j - 1], " "))
					return (p_err("Map must be surrounded by wall\n", 1), 1);
				if (ft_strchr(map->lines[i][j + 1], " "))
					return (p_err("Map must be surrounded by wall\n", 1), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	if_map_closed(int fd, t_map *map)
{
	char	*line;
	char	*join;

	line = get_next_line(fd);
	while (line && map->map_skip--)
	{
		free(line);
		line = get_next_line(fd);
	}
	join = NULL;
	while (line)
	{
		join = get_strnjoin(join, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	map->lines = ft_split(join, '\n');
	free(join);
	if (map_sides(map))
		return (p_err("Map must be surrounded by wall\n", 1), 0);
	replace_spaces(map);
	check_spaces(map);
	return (0);
}
