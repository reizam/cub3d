/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:37:37 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/16 17:37:37 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_key_hook(int keycode, t_vars *vars)
{
    printf("%d\n", keycode);
    return (1);
}

// W : 119
// A : 97
// D : 100
// S : 115

int     ft_render_screen(t_vars *vars)
{
}

void    ft_open_screen(t_cub *cub)
{
    t_vars    *vars;

    if (!(vars = (t_vars*)malloc(sizeof(t_vars))))
        return ;
    vars->posX = 0;
    vars->posY = 0;
    vars->mlx_ptr = mlx_init();
    vars->win_ptr = mlx_new_window(vars->mlx_ptr, cub->width, cub->height, "Cub3d");
    mlx_key_hook(vars->win_ptr, ft_key_hook, vars);
    mlx_loop_hook(vars->mlx_ptr, ft_render_screen, vars);
    mlx_loop(vars->mlx_ptr);
    free(vars->mlx_ptr);
    free(vars->win_ptr);
    free(vars);
}