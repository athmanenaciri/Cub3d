/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:41:00 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/19 15:35:16 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strchr(char c, char *ref)
{
	int	i;

	i = 0;
	while (ref[i])
	{
		if (c == ref[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	size_t	len;
	char	*copy;
	size_t	i;

	len = strlen(str);
	copy = malloc(len + 1);
	if (!copy)
		p_err("malloc error\n", 0);
	i = 0;
	while (i <= len)
	{
		copy[i] = str[i];
		i++;
	}
	return (copy);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;	

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;	

	i = 0;
	while (s1[i] && s2[i] && n--)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == ' ' && !s2[i])
		return (0);
	return (1);
}
