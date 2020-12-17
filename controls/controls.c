/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:31:32 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/17 15:31:32 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_key_hook(int keycode, t_vars *vars)
{
    t_cub *cub;
    double  temp;

    cub = vars->cub;
    if (keycode == W_KEY)
    {
        if (cub->map[(int)vars->posY][(int)(vars->posX + vars->dirX * vars->move_speed)] != '1')
            vars->posX += vars->dirX * vars->move_speed;
        if (cub->map[(int)(vars->posY + vars->dirY * vars->move_speed)][(int)vars->posX] != '1')
            vars->posY += vars->dirY * vars->move_speed;
    }       
    else if (keycode == A_KEY)
    {
        temp = vars->dirX;
        vars->dirX = vars->dirX * cos(vars->rot_speed) - vars->dirY * sin(vars->rot_speed);
        vars->dirY = temp * sin(vars->rot_speed) + vars->dirY * cos(vars->rot_speed);
        temp = vars->planeX;
        vars->planeX = vars->planeX * cos(vars->rot_speed) - vars->planeY * sin(vars->rot_speed);
        vars->planeY = temp * sin(vars->rot_speed) + vars->planeY * cos(vars->rot_speed);
    }
    else if (keycode == D_KEY)
    {
        temp = vars->dirX;
        vars->dirX = vars->dirX * cos(-vars->rot_speed) - vars->dirY * sin(-vars->rot_speed);
        vars->dirY = temp * sin(-vars->rot_speed) + vars->dirY * cos(-vars->rot_speed);
        temp = vars->planeX;
        vars->planeX = vars->planeX * cos(-vars->rot_speed) - vars->planeY * sin(-vars->rot_speed);
        vars->planeY = temp * sin(-vars->rot_speed) + vars->planeY * cos(-vars->rot_speed);
    }
    else if (keycode == S_KEY)
    {
        if (cub->map[(int)vars->posY][(int)(vars->posX - vars->dirX * vars->move_speed)] != '1')
            vars->posX -= vars->dirX * vars->move_speed;
        if (cub->map[(int)(vars->posY - vars->dirY * vars->move_speed)][(int)vars->posX] != '1')
            vars->posY -= vars->dirY * vars->move_speed;
    }
    return (1);
}