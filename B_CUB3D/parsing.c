/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:05:09 by okrich            #+#    #+#             */
/*   Updated: 2023/06/15 21:42:51 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_extension(char *file, char *ext)
{
	int	len;

	if (!file)
		return ;
	len = ft_strlen(file);
	while (*file)
	{
		if (!ft_strcmp(file, ext) && len > ft_strlen(ext))
			return ;
		file++;
	}
	p_err("File sould be folowed with .cub extention\n", 1);
}

char	*parse_texture(int fd, t_map *map)
{
	char	*line;
	int		all_tx[6];
	int		i;

	i = 0;
	while (i < 6)
		all_tx[i++] = 0;
	if (texture_check(fd, map, all_tx))
		return (close(fd), p_err("Invalid Map\n", 1), NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!empty_line(line))
			break ;
		map->map_skip++;
		line = get_next_line(fd);
	}
	return (line);
}

void	new_line_is_last(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			p_err("Map cannot be separated by empty line\n", 1);
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_map_content(char *line, t_map *map, int fd, int nb_player)
{
	int	i;

	while (line)
	{
		i = 0;
		if (line[i] == '\n')
			return (free(line), new_line_is_last(fd), nb_player);
		while (line[i] != '\0' && line[i] != '\n')
		{
			if (ft_strchr(line[i], "NSWE"))
				nb_player++;
			if (!ft_strchr(line[i], "01 NSWE"))
				return (close(fd), free(line),
					p_err("Expected : '01 NSWE'\n", 1), 0);
			i++;
		}
		if (map->map_width < i)
			map->map_width = i;
		free(line);
		map->map_height++;
		line = get_next_line(fd);
	}
	return (nb_player);
}

int	parse_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		nb_player;

	check_extension(file, ".cub");
	fd = ft_open(file);
	line = parse_texture(fd, map);
	nb_player = 0;
	nb_player = parse_map_content(line, map, fd, nb_player);
	if (nb_player == 0)
		p_err("There's no player\n", 1);
	else if (nb_player != 1)
		p_err("Player is duplicated\n", 1);
	return (1);
}
