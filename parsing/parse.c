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
    
    cub->error = "Wrong resolution...";
    width = ft_atoi(line);
    height = ft_atoi(line + ft_nb_len(width) + 1);
    if (ft_strlen(line) != ft_nb_len(width) + ft_nb_len(height) + (size_t)1)
        return (0);
    cub->width = width;
    cub->height = height;
    return (width != 0 && height != 0);
}

char    *ft_get_values(char *line, int i)
{
    while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
        i++;
    return (line + i);
}

int     ft_parse_line(char *line, t_cub *cub)
{
    int i;

    i = 0;
    while (line[i] == ' ' || (line >= 9 && line <= 13))
        i++;
    if (ft_strncmp(line + i, "R ", 2) == 0)
        return (ft_parse_res(ft_get_values(line, i + 1), cub));
    else if (ft_strncmp(line + i, "NO ", 3) == 0)
        return (ft_parse_texture(ft_get_values(line, i + 2), 0, cub));
    else if (ft_strncmp(line + i, "SO ", 3) == 0)
        return (ft_parse_texture(ft_get_values(line, i + 2), 1, cub));
    else if (ft_strncmp(line + i, "WE ", 3) == 0)
        return (ft_parse_texture(ft_get_values(line, i + 2), 2, cub));
    else if (ft_strncmp(line + i, "EA ", 3) == 0)
        return (ft_parse_texture(ft_get_values(line, i + 2), 3, cub));
    else if (ft_strncmp(line + i, "S ", 2) == 0)
        return (ft_parse_texture(ft_get_values(line, i + 1), 4, cub));
    else if (ft_strncmp(line + i, "F ", 2) == 0) 
        return (ft_parse_rgb(ft_get_values(line, i + 1), 0, cub));
    else if (ft_strncmp(line + i, "C ", 2) == 0)
        return (ft_parse_rgb(ft_get_values(line, i + 1), 1, cub));
    return (0);
}

t_cub   *ft_create_cub()
{
    t_cub   *cub;

    if (!(cub = (t_cub*)malloc(sizeof(t_cub))))
        return (NULL);
    cub->spawn_x = 0;
    cub->spawn_y = 0;
    cub->save_first_image = 0;
    cub->height = 0;
    cub->width = 0;
    cub->dir_x = 0;
    cub->dir_y = 0;
    cub->plane_x = 0;
    cub->plane_y = 0;
    cub->south_texture = NULL;
    cub->west_texture = NULL;
    cub->east_texture = NULL;
    cub->north_texture = NULL;
    cub->sprite_texture = NULL;
    cub->rgb_ground = -1;
    cub->rgb_roof = -1;
    cub->map = NULL;
    cub->error = "";
    return (cub);
}

t_cub   *ft_parse_cub_file(char *file)
{
    char    *line;
    int     fd;
    int     i;
    t_cub   *cub;

    if (!(cub = (t_cub*)ft_create_cub()))
        return (ft_parse_exit(cub));
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (ft_parse_exit(cub));
    while (!ft_is_full(cub) && get_next_line(fd, &line) > 0)
    {
        if (line != NULL && ft_strlen(line) > 0)
            i = ft_parse_line(line, cub);
        free(line);
        if (!i)
        {
            close(fd);
            return (ft_parse_exit(cub));
        }
    }
    if (!ft_is_full(cub) || !ft_parse_map(fd, cub))
        return (ft_parse_exit(cub));
    close(fd);
    return (cub);
}
