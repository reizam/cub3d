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

    cub = vars->cub;
    if (keycode == W_KEY)
    {
        if (cub->map[(int)vars->posY][(int)(vars->posX + vars->dirX * vars->move_speed)] != '1')
            vars->posX += vars->dirX * vars->moveSpeed;
        if (cub->map[(int)(vars->posY + vars->dirY * vars->move_speed)][(int)vars->posX] != '1')
            vars->posY += vars->dirY * vars->moveSpeed;
    }       
    else if (keycode == A_KEY)
    {

    }
    else if (keycode == D_KEY)
    {

    }
    else if (keycode == S_KEY)
    {

    }
    return (1);
}