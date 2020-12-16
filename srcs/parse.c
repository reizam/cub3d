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
    return (1);
}

int     ft_parse_rgb(char *line, int id, t_cub *cub)
{
    return (1);
}

int     ft_parse_line(char *line, int fd, t_cub *cub)
{
    if (ft_strncmp(line, "R ", 2))
        return (ft_parse_res(line + 2, cub));
    else if (ft_strncmp(line, "NO ", 3))
        return (ft_parse_path(line, 0, cub));
    else if (ft_strncmp(line, "SO ", 3))
        return (ft_parse_path(line, 1, cub));
    else if (ft_strncmp(line, "WE ", 3))
        return (ft_parse_path(line, 2, cub));
    else if (ft_strncmp(line, "EA ", 3))
        return (ft_parse_path(line, 3, cub));
    else if (ft_strncmp(line, "S ", 2))
        return (ft_parse_path(line, 4, cub));
    else if (ft_strncmp(line, "F ", 2)) 
        return (ft_parse_rgb(line, 0, cub));
    else if (ft_strncmp(line, "C ", 2))
        return (ft_parse_rgb(line, 1, cub));
    else if (ft_check_line(line))
        return (ft_parse_map(line, fd, cub));
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
    fd = open(file, O_RDONLY);
    while ((i = get_next_line(&line, fd)) > 0)
    {
        if (line[0] && line != NULL)
            i = ft_parse_line(line, fd, cub);
        free(line);
        line = NULL;
        if (!i)
        {
            free_cub(cub);
            return (NULL);
        }
    }
    if (i == 0 && line != NULL)
    {
        if (line[0] && line != NULL)
            i = ft_parse_line(line, fd, cub);
        free(line);
        line = NULL;
    }
    close(fd);
    return (cub);
}