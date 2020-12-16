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
        return (NULL);
    screen->mlx_ptr = mlx_init();
    screen->win_ptr = mlx_new_window(mlx_ptr, cub->width, cub->height, "Cub3d");
    mlx_loop(mlx_ptr);
    free(mlx_ptr);
    free(win_ptr);
    free(screen);
}