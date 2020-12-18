/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 08:00:13 by marvin            #+#    #+#             */
/*   Updated: 2020/12/16 08:00:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub *ft_parse_exit(t_cub *cub)
{
    int         i;

    i = 0;
    if (!cub)
        return (NULL);
    if (cub->east_texture)
        free(cub->east_texture);
    if (cub->west_texture)
        free(cub->west_texture);
    if (cub->south_texture)
        free(cub->south_texture);
    if (cub->north_texture)
        free(cub->north_texture);
    if (cub->sprite_texture)
        free(cub->sprite_texture);
    if (cub->map)
    {
        while (cub->map[i])
            free(cub->map[i++]);
        free(cub->map);
    }
    free(cub);
    return (NULL);
}

void    ft_screen_exit(t_vars *vars)
{
    if (vars->img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
    mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
    if (vars->win_ptr)
        free(vars->win_ptr);
    ft_parse_exit(vars->cub);
    vars->cub = NULL;
    free(vars);
    vars = NULL;
}
