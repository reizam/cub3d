/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:23:05 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/17 17:23:05 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_draw_pixel(t_vars *vars, int x, int y, int color)
{
    char    *dst;

    dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    ft_draw_ver_line_tex(t_vars *vars, t_img img, int x, int line_height, int texX)
{
    int y_increment;
    int y;
    int i;

    y_increment = (line_height * 2) / img.height;
    y = vars->cub->height / 2 - line_height;
    i = -1;
    while (++i < img.height)
    {
        ft_draw_pixel(vars, x, y, img.addr[img->img_width * i + texX]);
        y += y_increment;
    }
}

void    ft_draw_ver_line(t_vars *vars, int x, int start_y, int end_y, int color)
{
    int dx;
    int dy;
    int e;

    e = end_y - start_y;
    dx = 0;
    dy = e * 2;
    while (start_y <= end_y)
    {
        ft_draw_pixel(vars, x, start_y, color);
        start_y++;
        if ((e = e - dx) <= 0)
        {
            x++;
            e += dy;
        }
    }
}
