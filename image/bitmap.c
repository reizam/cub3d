/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:08:49 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/22 22:08:49 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_write_bmp_file_header(t_vars *vars, int fd)
{
    int i;
    
    i = 58 + (vars->cub->width * vars->cub->height) * 4;
    write(fd, "BM", 2);
    write(fd, &i, 4);
    write(fd, "\0\0\0\0", 4);
    i = 58;
    write(fd, &i, 4);
}

void    ft_write_bmp_info_header(t_vars *vars, int fd)
{
    int i;

    i = 40;
    write(fd, &i, 4);
    write(fd, &vars->cub->width, 4);
    write(fd, &vars->cub->height, 4);
    i = 1;
    write(fd, &i, 2);
    write(fd, &vars->bits_per_pixel, 2);
    i = -1;
    while (++i < 28)
        write(fd, "\0", 1);
}

void    ft_update_pixel(t_vars *vars, int i, int *j, int k)
{
    char    t;
    int     l;

    l = 3;
    while (l >= 0)
    {
        t = vars->addr[*j + (i * vars->line_length)];
        vars->addr[*j + (i * vars->line_length)] = vars->addr[k - l + (i * vars->line_length - 1)];
        vars->addr[k - l + (i * vars->line_length - 1)] = t;
        l--;
        (*j)++;
    }    
}

void    ft_update_img(t_vars *vars)
{
    int i;
    int j;
    int k;

    i = -1;
    while (++i < vars->cub->height)
    {
        j = 0;
        k = vars->line_length;
        while (j < k && j != k)
        {
            ft_update_pixel(vars, i, &j, k);
            k -= 4;
        }
    }
}

void    ft_save_image(t_vars *vars, char *file_name)
{
    int fd;
    int i;

    fd = open(file_name, O_CREAT | O_RDWR, 0777);
    if (fd <= 0)
        return ;
    ft_write_bmp_file_header(vars, fd);
    ft_write_bmp_info_header(vars, fd);
    ft_update_img(vars);
    i = vars->cub->width * vars->cub->height - 1;
    while (i >= 0)
    {
        write(fd, &vars->addr[i * vars->bits_per_pixel / 8], 4);
        i--;
    }
    close(fd);
}