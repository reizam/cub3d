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

void    ft_calc_side_dist(int )
{
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (vars->posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (vars->posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
    }
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