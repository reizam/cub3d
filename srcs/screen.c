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

void    ft_open_screen(t_cub *cub)
{
    t_screen    *screen;

    if (!(screen = (t_screen*)malloc(sizeof(t_screen))))
        return ;
    screen->mlx_ptr = mlx_init();
    screen->win_ptr = mlx_new_window(screen->mlx_ptr, cub->width, cub->height, "Cub3d");
    mlx_loop(screen->mlx_ptr);
    free(screen->mlx_ptr);
    free(screen->win_ptr);
    free(screen);
}