/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:31:37 by okrich            #+#    #+#             */
/*   Updated: 2023/06/18 20:06:07 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	parse_color(char *line)
{
	int	i;
	int	comma;

	i = 1;
	comma = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		p_err("Expected color value\n", 1);
	while (line[i] && line[i] != '\n')
	{
		if (ft_strchr(line[i], " ,") || (line[i] >= '0' && line[i] <= '9'))
		{
			if (line[i] == ',')
				comma++;
		}
		else
			p_err("Invalid character in color value\n", 1);
		if (comma > 2)
			p_err("Comma is repeated more than twice\n", 1);
		i++;
	}
}

int	get_color(char *line, int *n)
{
	char	**col;	
	int		i;
	int		nb[3];
	int		hex;

	*n += 1;
	i = -1;
	parse_color(line);
	while (line[++i])
		if (line[i] >= '0' && line[i] <= '9')
			break ;
	col = ft_split(line + i, ',');
	i = 0;
	while (col[i])
	{
		nb[i] = ft_atoi(col[i]);
		if (nb[i] == -1)
			return (free_words(col), exit(1), 0);
		i++;
	}
	free_words(col);
	if (i != 3)
		p_err("Error in rgb\n", 1);
	hex = (nb[0] << 16) + (nb[1] << 8) + nb[2];
	return (hex);
}

char	*get_texture(char *line, int *all_tx)
{
	char	*tex;
	char	**spl_tex;
	char	**tmp;
	int		i;

	i = 0;
	*all_tx += 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		p_err("texture content not valid\n", 1);
	tmp = ft_split(line + i, '\n');
	spl_tex = ft_split(tmp[0], ' ');
	free_words(tmp);
	if (!spl_tex || spl_tex[1])
		p_err("texture content not valid\n", 1);
	tex = ft_strdup(spl_tex[0]);
	free_words(spl_tex);
	return (tex);
}

int	parse_info_map(char *line, int *all_tx, t_map *map)
{
	if (!ft_strncmp(line, "NO", 2) && !all_tx[0])
		map->no_text = get_texture(line + 2, &all_tx[0]);
	else if (!ft_strncmp(line, "SO", 2) && !all_tx[1])
		map->so_text = get_texture(line + 2, &all_tx[1]);
	else if (!ft_strncmp(line, "WE", 2) && !all_tx[2])
		map->we_text = get_texture(line + 2, &all_tx[2]);
	else if (!ft_strncmp(line, "EA", 2) && !all_tx[3])
		map->ea_text = get_texture(line + 2, &all_tx[3]);
	else if (!ft_strncmp(line, "F", 1) && !all_tx[4])
		map->floor_hex = get_color(line, &all_tx[4]);
	else if (!ft_strncmp(line, "C", 1) && !all_tx[5])
		map->ceil_hex = get_color(line, &all_tx[5]);
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
		if (empty_line(line))
		{
			line = get_next_line(fd);
			continue ;
		}
		if (parse_info_map(line, all_tx, map))
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
