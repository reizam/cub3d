/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 14:19:12 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/25 14:19:12 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_line(char *line)
{
	int i;

	i = -1;
	while (line && line[++i])
		if (!ft_is_map_char(line[i], 0))
			return (0);
	return (1);
}

int	ft_check_circle_map(t_cub *cub, int type, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (type == 0 || type == 4 || type == 5)
		x = -1;
	if (type == 1 || type == 5 || type == 7)
		x = 1;
	if (type == 2 || type == 6 || type == 7)
		y = 1;
	if (type == 3 || type == 4 || type == 6)
		y = -1;
	while (j >= 0 && i >= 0 && cub->map[i]
	&& cub->map[i][j] && cub->map[i][j] != '1')
	{
		if (cub->map[i][j] == ' ')
			return (0);
		j += x;
		i += y;
	}
	return (j >= 0 && i >= 0 && cub->map[i]
	&& cub->map[i][j] && cub->map[i][j] == '1');
}

int	ft_check_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != '0' && cub->map[i][j] != '2'
			&& !ft_is_map_char(cub->map[i][j], 1))
				continue ;
			if (!ft_check_circle_map(cub, 0, i, j)
			|| !ft_check_circle_map(cub, 1, i, j)
			|| !ft_check_circle_map(cub, 2, i, j)
			|| !ft_check_circle_map(cub, 3, i, j)
			|| !ft_check_circle_map(cub, 4, i, j)
			|| !ft_check_circle_map(cub, 5, i, j)
			|| !ft_check_circle_map(cub, 6, i, j)
			|| !ft_check_circle_map(cub, 7, i, j))
				return (0);
		}
	}
	return (1);
}

int	ft_leave_parse_map(char *map)
{
	if (map)
		free(map);
	return (0);
}
