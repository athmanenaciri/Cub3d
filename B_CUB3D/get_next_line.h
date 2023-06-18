/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:18:07 by anaciri           #+#    #+#             */
/*   Updated: 2023/06/18 19:23:01 by anaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<unistd.h> 

//get_next_line.c file
char	*ft_strndup(char *s1, ssize_t n, ssize_t *fail);
ssize_t	check_newline(char *reader);
char	*get_resteofline(ssize_t n, char **rest);
ssize_t	read_and_get_line(ssize_t	n, int fd, char **line, char **rest);
char	*get_next_line(int fd);

//getnext_utils.c file
ssize_t	ft_strlen(char *str);
char	*ft_strncpy(char *dst, char *src, ssize_t dstsize);
char	*get_strnjoin(char *s1, char *s2, ssize_t i);

#endif
