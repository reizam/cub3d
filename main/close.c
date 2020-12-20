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
    {
        ft_print_error("A malloc failed");
        return (NULL);
    }
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
    if (ft_strlen(cub->error) > 0)
        ft_print_error(cub->error);
    free(cub);
    return (NULL);
}

void    ft_screen_init_exit(t_vars *vars, int do_exit)
{
    if (vars->textures[0].define && vars->textures[0].img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->textures[0].img_ptr);
    if (vars->textures[1].define && vars->textures[1].img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->textures[1].img_ptr);
    if (vars->textures[2].define && vars->textures[2].img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->textures[2].img_ptr);
    if (vars->textures[3].define && vars->textures[3].img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->textures[3].img_ptr);
    if (do_exit)
    {
        vars->cub->error = "A texture is corrupt.";
        ft_parse_exit(vars->cub);
        free(vars);
        exit(1);
    }
}

void    ft_screen_exit(t_vars *vars)
{
    mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
    ft_screen_init_exit(vars, 0);
    mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
    free(vars->mlx_ptr);
    ft_parse_exit(vars->cub);
    vars->cub = NULL;
    free(vars);
    vars = NULL;
    exit(0);
}
