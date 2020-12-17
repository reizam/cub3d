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

void    ft_move(t_vars *vars, int dir)
{
    if (vars->cub->map[(int)vars->posY][(int)(vars->posX + (dir * (vars->dirX * vars->move_speed)))] != '1')
        vars->posX += dir * (vars->dirX * vars->move_speed);
    if (vars->cub->map[(int)(vars->posY + (dir * (vars->dirX * vars->move_speed)))][(int)vars->posX] != '1')
        vars->posY += dir * (vars->dirY * vars->move_speed);
}

void    ft_rot(t_vars *vars, int dir)
{
    double temp;

    temp = vars->dirX;
    vars->dirX = vars->dirX * cos(vars->rot_speed * dir) - vars->dirY * sin(vars->rot_speed * dir);
    vars->dirY = temp * sin(vars->rot_speed * dir) + vars->dirY * cos(vars->rot_speed * dir);
    temp = vars->planeX;
    vars->planeX = vars->planeX * cos(vars->rot_speed * dir) - vars->planeY * sin(vars->rot_speed * dir);
    vars->planeY = temp * sin(vars->rot_speed * dir) + vars->planeY * cos(vars->rot_speed * dir);
}

int     ft_key_hook(int keycode, t_vars *vars)
{
    if (keycode == W_KEY)
        ft_move(vars, 1);
    else if (keycode == A_KEY)
        ft_rot(vars, 1);
    else if (keycode == D_KEY)
        ft_rot(vars, -1);
    else if (keycode == S_KEY)
        ft_move(vars, -1);
    else if (keycode == ESC_KEY)
        ft_screen_exit(vars);
    return (1);
}