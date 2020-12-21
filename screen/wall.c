/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:47:34 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/18 16:47:34 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_draw_wall_line(t_vars *vars, int x, int j[5], double i[8])
{
    int     k[4];
    double  wall_x;
    t_img   img;
    
    k[2] = (int)(vars->cub->height / i[7]);
    k[0] = -k[2] / 2 + vars->cub->height / 2;
    k[0] = k[0] < 0 ? 0 : k[0];
    k[1] = k[2] / 2 + vars->cub->height / 2;
    k[1] = k[1] >= vars->cub->height ? vars->cub->height - 1 : k[1];
    wall_x = j[4] == 0 ? (vars->posY + i[7] * i[2]) : (vars->posX + i[7] * i[1]);
    wall_x -= floor((wall_x));
    if (j[4] == 0)
        j[4] = j[2] > 0 ? 0 : 1;
    else
        j[4] = j[3] > 0 ? 2 : 3;
    img = vars->textures[j[4]];
    k[3] = (int)(wall_x * (double)img.width);
    k[3] = img.width - k[3] - 1;
    ft_draw_texture_line(vars, img, x, k);
}

void    ft_draw_wall(t_vars *vars)
{
    int i;
    int x;
    int hit;

    x = -1;
    while (++x < vars->cub->width)
    {
        hit = 0;

    }
}