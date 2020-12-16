/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:49:01 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 16:50:57 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t s2_size)
{
	char			*result;
	ssize_t			i;
	ssize_t			j;

	i = (s1 == NULL ? 0 : ft_strlen(s1)) + s2_size;
	if (!(result = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2 && j < s2_size)
		result[i++] = s2[j++];
	result[i] = 0;
	if (s1)
		free(s1);
	return (result);
}

ssize_t	get_next_line_offset(char *str)
{
	ssize_t i;

	i = 0;
	while (str && str[i])
		if (str[i++] == '\n')
			return (i);
	return (0);
}

int		get_and_copy_line(char *str, char **line, ssize_t end)
{
	char		*result;
	ssize_t		i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (end + 1))))
	{
		if (str)
			free(str);
		return (0);
	}
	while (i < end)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = 0;
	*line = result;
	return (1);
}

int		get_and_free_str(ssize_t start, char **gnl, int fd)
{
	char	*result;
	ssize_t	i;

	i = ft_strlen(gnl[fd]) - start;
	if (i <= 0)
	{
		if (gnl[fd])
			free(gnl[fd]);
		gnl[fd] = 0;
		return (1);
	}
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
	{
		if (gnl[fd])
			free(gnl[fd]);
		return (0);
	}
	i = 0;
	while (gnl[fd] && gnl[fd][start])
		result[i++] = gnl[fd][start++];
	result[i] = 0;
	if (gnl[fd])
		free(gnl[fd]);
	gnl[fd] = result;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*gnl[500];
	char		buffer[1025];
	ssize_t		i;
	ssize_t		j;

	if (!line || fd < 0)
		return (-1);
	while ((i = read(fd, buffer, 1024)) >= 0)
	{
		if (i > 0)
			gnl[fd] = ft_strjoin_gnl(gnl[fd], buffer, i);
		if (((j = get_next_line_offset(gnl[fd])) > 0) || i == 0)
			break ;
	}
	if (i < 0)
		return (-1);
	i = ft_strlen(gnl[fd]);
	if (!(get_and_copy_line(gnl[fd], line, j == 0 && i >= 0 ? i : j - 1)))
		return (-1);
	if (!(get_and_free_str(j == 0 && i >= 0 ? i : j, gnl, fd)))
		return (-1);
	return (j == 0 ? 0 : 1);
}
