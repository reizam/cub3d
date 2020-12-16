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

int     ft_is_map_char(char c)
{
    return (c == '1' || c == '2' || c == '0' || c == 'N' || c =='S' || c == 'E' || c == 'W');
}

int     ft_check_line(char *line)
{
    size_t i;

    i = 0;
    while (line[i])
    {
        if (!ft_is_map_char(line[i]))
            return (0);
        i++;
    }
    return (1);
}

int     **parse_map(char *line, int fd, t_cub *cub)
{
}