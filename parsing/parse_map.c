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

void    ft_set_spawn(t_cub *cub, char c)
{
    if (c == 'E')
    {
        cub->dir_x = 1;
        cub->plane_y = -0.66;
    }
    if (c == 'W')
    {
        cub->dir_x = -1;
        cub->plane_y = 0.66;
    }
    if (c == 'S')
    {
        cub->dir_y = 1;
        cub->plane_x = 0.66;
    }
    if (c == 'N')
    {
        cub->dir_y = -1;
        cub->plane_y = -0.66;
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
                if (cub->spawn_x > 0 || cub->spawn_x > 0)
                    return (0);
                cub->spawn_x = j;
                cub->spawn_y = i;
                ft_set_spawn(cub, cub->map[i][j]);
            }
    }
    return (cub->dir_x != 0 || cub->dir_y != 0);
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
        k = j == 0 && ft_strlen(line) == 0 ? 2 : k;
        i = ft_check_map_line(line);
        if (i && k == 1)
            map = ft_strjoin(map, line, j);
        free(line);
        if (!i && k == 1)
        {
            free(map);
            return (0);
        }
        if (j <= 0 || k == 2)
            break ;
    }
    cub->map = ft_split(map, '\n');
    free(map);
    return (ft_check_map(cub) && ft_parse_map_param(cub));
}
