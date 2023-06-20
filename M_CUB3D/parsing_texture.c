/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:31:37 by okrich            #+#    #+#             */
/*   Updated: 2023/06/20 15:58:08 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_color(char *line, int fd)
{
	int	i;
	int	comma;

	i = 1;
	comma = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (close(fd), p_err("Expected color value\n", 1), 1);
	while (line[i] && line[i] != '\n')
	{
		if (ft_strchr(line[i], " ,") || (line[i] >= '0' && line[i] <= '9'))
		{
			if (line[i] == ',')
				comma++;
		}
		else
			return (close(fd), p_err("Invalid character in color\n", 1), 1);
		if (comma > 2)
			return (close(fd), p_err("error in comma\n", 1), 1);
		i++;
	}
	return (1);
}

int	get_color(char *line, int *n, int fd)
{
	char	**col;	
	int		i;
	int		nb[3];
	int		hex;

	*n += 1;
	i = -1;
	parse_color(line, fd);
	while (line[++i])
		if (line[i] >= '0' && line[i] <= '9')
			break ;
	col = ft_split(line + i, ',', fd);
	i = 0;
	while (col[i])
	{
		nb[i] = ft_atoi(col[i]);
		if (nb[i] == -1)
			return (close(fd), free_words(col), exit(1), 0);
		i++;
	}
	free_words(col);
	if (i != 3)
		return (close(fd), p_err("Error in rgb\n", 1), 1);
	hex = (nb[0] << 16) + (nb[1] << 8) + nb[2];
	return (hex);
}

char	*get_texture(char *line, int *all_tx, int fd)
{
	char	*tex;
	char	**spl_tex;
	char	**tmp;
	int		i;

	i = 2;
	*all_tx += 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (close(fd), p_err("texture content not valid\n", 1), NULL);
	tmp = ft_split(line + i, '\n', fd);
	spl_tex = ft_split(tmp[0], ' ', fd);
	free_words(tmp);
	if (!spl_tex || spl_tex[1])
		return (close(fd), p_err("texture content not valid\n", 1), NULL);
	tex = ft_strdup(spl_tex[0]);
	free_words(spl_tex);
	if (!tex)
		return (free(line), close(fd), exit(1), NULL);
	return (tex);
}

int	parse_info_map(char *line, int *all_tx, t_map *map, int fd)
{
	if (!ft_strncmp(line, "NO", 2) && !all_tx[0])
		map->no_text = get_texture(line, &all_tx[0], fd);
	else if (!ft_strncmp(line, "SO", 2) && !all_tx[1])
		map->so_text = get_texture(line, &all_tx[1], fd);
	else if (!ft_strncmp(line, "WE", 2) && !all_tx[2])
		map->we_text = get_texture(line, &all_tx[2], fd);
	else if (!ft_strncmp(line, "EA", 2) && !all_tx[3])
		map->ea_text = get_texture(line, &all_tx[3], fd);
	else if (!ft_strncmp(line, "F", 1) && !all_tx[4])
		map->floor_hex = get_color(line, &all_tx[4], fd);
	else if (!ft_strncmp(line, "C", 1) && !all_tx[5])
		map->ceil_hex = get_color(line, &all_tx[5], fd);
	else
		return (0);
	return (1);
}

int	texture_check(int fd, t_map *map, int *all_tx)
{
	char	*line;
	int		nb;

	nb = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->map_skip++;
		if (empty_line(line, fd))
		{
			line = get_next_line(fd);
			continue ;
		}
		if (parse_info_map(line, all_tx, map, fd))
			nb++;
		else
			return (free(line), 1);
		free(line);
		if (nb == 6)
			break ;
		line = get_next_line(fd);
	}
	return (0);
}
