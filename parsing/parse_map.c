/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:19:28 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 18:09:43 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_is_map_char(char c, int just_spawn)
{
    if (just_spawn)
        return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
    return (c == '1' || c == '2' || c == '0' || c == 'N' || c =='S' || c == 'E' || c == 'W' || c == ' ');
}

int ft_check_map_line(char *line)
{
    int i;

    i = -1;
    while (line && line[++i])
        if (!ft_is_map_char(line[i], 0))
            return (0);
    return (i > 0);
}

int     ft_check_circle_map(t_cub *cub, int x, int y, int i, int j)
{
    while (cub->map[i] && cub->map[i][j] && cub->map[i][j] != '1')
    {
        if (cub->map[i][j] == ' ')
            return (0);
        j += x;
        i += y;
    }
    return (cub->map[i] && cub->map[i][j] && cub->map[i][j] == '1');
}

int     ft_check_map(t_cub *cub)
{
    int i;
    int j;

    i = -1;
    while (cub->map[++i])
    {
        j = -1;
        while (cub->map[i][++j])
        {
            if (cub->map[i][j] != '0')
                continue ;
            if (!ft_check_circle_map(cub, 0, -1, i, j))
                return (0);
            if (!ft_check_circle_map(cub, 0, 1, i, j))
                return (0);
            if (!ft_check_circle_map(cub, -1, 0, i, j))
                return (0);
            if (!ft_check_circle_map(cub, 1, 0, i, j))
                return (0);
        }
    }
    return (1);
}

void    ft_set_spawn(t_cub *cub, char c)
{
    if (c == 'E')
    {
        cub->dirX = 1;
        cub->planeY = -0.66;
    }
    if (c == 'W')
    {
        cub->dirX = -1;
        cub->planeY = 0.66;
    }
    if (c == 'S')
    {
        cub->dirY = 1;
        cub->planeX = 0.66;
    }
    if (c == 'N')
    {
        cub->dirY = -1;
        cub->planeX = -0.66;
    }
}

int ft_parse_map_param(t_cub *cub)
{
    int i;
    int j;

    i = -1;
    while (cub->map[++i])
    {
        j = -1;
        while (cub->map[i][++j])
            if (ft_is_map_char(cub->map[i][j], 1))
            {
                if (cub->spawnX > 0 || cub->spawnX > 0)
                    return (0);
                cub->spawnX = j;
                cub->spawnY = i;
                ft_set_spawn(cub, cub->map[i][j]);
            }
    }
    return (1);
}

int ft_parse_map(int fd, t_cub *cub)
{
    char    *map;
    char    *line;
    int     i;
    int     j;
    int     k;

    k = 0;
    map = NULL;
    cub->error = "Wrong map.";
    while ((j = get_next_line(fd, &line)) >= 0)
    {
        k = ft_strlen(line) > 0 && !k ? 1 : k;
        if (j == 0 && ft_strlen(line) == 0)
            k = 2;
        i = ft_check_map_line(line);
        if (i && k == 1)
            map = ft_strjoin(map, line, j);
        free(line);
        if (k == 2)
            break ;
        if (!i && k)
        {
            free(map);
            return (0);
        }
        if (j <= 0)
            break ;
    }
    cub->map = ft_split(map, '\n');
    free(map);
    return (ft_check_map(cub) && ft_parse_map_param(cub));
}
