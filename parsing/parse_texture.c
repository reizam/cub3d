/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:01:48 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/18 14:01:48 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_check_file(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd <= -1)
        return (0);
    close(fd);
    return (ft_check_file_ext(file, ".xpm"));
}

int     ft_parse_texture(char *line, int id, t_cub *cub)
{
    cub->error = 2;
    if (id == 0)
        cub->north_texture = ft_strdup(line);
    else if (id == 1)
        cub->south_texture = ft_strdup(line);
    else if (id == 2)
        cub->west_texture = ft_strdup(line);
    else if (id == 3)
        cub->east_texture = ft_strdup(line);
    else if (id == 4)
        cub->sprite_texture = ft_strdup(line);
    return (1);
}