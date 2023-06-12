#include "cub3D.h"

int	count(char *s, char c)
{
	int	x;

	x = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s && *s != c)
			s++;
		x++;
	}
	return (x);
}

void	free_words(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	*get_str(char *s, char c, char **strs)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	while (len)
	{
		if (s[i] == c)
			break ;
		i++;
		len--;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		free_words(strs);
		exit(1);
	}
	ft_strncpy(str, s, i);
	return (str);
}

char	*skip(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		count_str;
	int		i;

	if (s == NULL)
		return (NULL);
	s = skip(s, c);
	count_str = count(s, c);
	strs = malloc(sizeof(char *) * (count_str + 1));
	if (strs == NULL)
		exit (1);
	i = 0;
	while (i < count_str)
	{
		strs[i] = get_str(s, c, strs);
		while (*s && *s != c)
			s++;
		s = skip(s, c);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
