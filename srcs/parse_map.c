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

int ft_is_map_char(char c)
{
    return (c == '1' || c == '2' || c == '0' || c == 'N' || c =='S' || c == 'E' || c == 'W');
}

int ft_check_map_line(char *line)
{
    int i;

    i = -1;
    while (line && line[++i])
        if (!ft_is_map_char(line[i]))
            return (0);
    return (i > 0);
}

int ft_check_map(t_cub *cub)
{
    (void)cub;
    return (1);
}

int ft_parse_map(int fd, t_cub *cub)
{
    char    *map;
    char    *line;
    int     i;
    int     j;

    while ((j = get_next_line(fd, &line) >= 0)
    {
        i = ft_check_map_line(line);
        if (i)
            map = ft_strjoin(map, line, j);
        free(line);
        if (!i)
        {
            free(map);
            return (0);
        }
        if (j == 0)
            break ;
    }
    cub->map = ft_split(map, '\n');
    free(map); 
    return (ft_check_map(cub));
}
