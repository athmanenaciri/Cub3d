/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnext_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:56:53 by okrich            #+#    #+#             */
/*   Updated: 2023/06/18 20:05:21 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

ssize_t	ft_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dst, char *src, ssize_t dstsize)
{
	ssize_t	j;

	if (dstsize == 0)
		return (dst);
	j = 0;
	while (dstsize-- && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*get_strnjoin(char *s1, char *s2, ssize_t i)
{
	char	*join;
	ssize_t	len;

	len = ft_strlen(s1);
	join = malloc(sizeof(char) * (len + i + 1));
	if (join == NULL)
		return (NULL);
	ft_strncpy(join, s1, len);
	ft_strncpy(join + len, s2, i);
	free (s1);
	return (join);
}
