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

int     ft_parse_line(char *line, t_cub *cub)
{
    if (ft_strncmp(line, "R ", 2) == 0)
        return (ft_parse_res(line + 2, cub));
    else if (ft_strncmp(line, "NO ", 3) == 0)
        return (ft_parse_texture(line + 3, 0, cub));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return (ft_parse_texture(line + 3, 1, cub));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return (ft_parse_texture(line + 3, 2, cub));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return (ft_parse_texture(line + 3, 3, cub));
    else if (ft_strncmp(line, "S ", 2) == 0)
        return (ft_parse_texture(line + 3, 4, cub));
    else if (ft_strncmp(line, "F ", 2) == 0) 
        return (ft_parse_rgb(line + 2, 0, cub));
    else if (ft_strncmp(line, "C ", 2) == 0)
        return (ft_parse_rgb(line + 2, 1, cub));
    return (0);
}

t_cub   *ft_create_cub()
{
    t_cub   *cub;

    if (!(cub = (t_cub*)malloc(sizeof(t_cub))))
        return (NULL);
    cub->save_first_image = 0;
    cub->height = 0;
    cub->width = 0;
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
            return (ft_parse_exit(cub));
    }
    if (!ft_is_full(cub) || !ft_parse_map(fd, cub))
        return (ft_parse_exit(cub));
    close(fd);
    return (cub);
}
