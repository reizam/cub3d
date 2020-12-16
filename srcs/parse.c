/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:05:58 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 18:23:22 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_parse_res(char *line, t_cub *cub)
{
    int height;
    int width;
    
    width = ft_atoi(line);
    height = ft_atoi(line + ft_nb_len(width) + 1);
    if (ft_strlen(line) != ft_nb_len(width) + ft_nb_len(height) + 1)
        return (0);
    cub->width = width;
    cub->height = height;
    return (width != 0 && height != 0);
}

int     ft_parse_path(char *line, int id, t_cub *cub)
{
    if (id == 0)
        cub->north_texture = line;
    else if (id == 1)
        cub->south_texture = line;
    else if (id == 2)
        cub->west_texture = line;
    else if (id == 3)
        cub->east_texture = line;
    else if (id == 4)
        cub->sprite_texture = line;
    return (1);
}

int     ft_parse_line(char *line, t_cub *cub)
{
    if (ft_strncmp(line, "R ", 2))
        return (ft_parse_res(line + 2, cub));
    else if (ft_strncmp(line, "NO ", 3))
        return (ft_parse_path(line + 3, 0, cub));
    else if (ft_strncmp(line, "SO ", 3))
        return (ft_parse_path(line + 3, 1, cub));
    else if (ft_strncmp(line, "WE ", 3))
        return (ft_parse_path(line + 3, 2, cub));
    else if (ft_strncmp(line, "EA ", 3))
        return (ft_parse_path(line + 3, 3, cub));
    else if (ft_strncmp(line, "S ", 2))
        return (ft_parse_path(line + 3, 4, cub));
    else if (ft_strncmp(line, "F ", 2)) 
        return (ft_parse_rgb(line, 0, cub));
    else if (ft_strncmp(line, "C ", 2))
        return (ft_parse_rgb(line, 1, cub));
    return (0);
}

t_cub   *ft_parse_cub_file(char *file)
{
    char    *line;
    int     fd;
    int     i;
    t_cub   *cub;

    if (!(cub = (t_cub*)malloc(sizeof(t_cub))))
        return (NULL);
    cub->r_ground = -1;
    cub->r_roof = -1;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (parse_exit(cub));
    while (!ft_is_full(cub) && get_next_line(fd, &(line = NULL)) > 0)
    {
        if (line != NULL && ft_strlen(line) > 0)
            i = ft_parse_line(line, fd, cub)
        free(line);
        if (!i)
            return (parse_exit(cub));
    }
    if (!ft_is_full(cub) || !ft_parse_map(fd, cub))
        return (parse_exit(cub));
    close(fd);
    return (cub);
}
