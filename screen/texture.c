/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:47:04 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/18 16:47:04 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_load_texture(t_vars *vars, t_img texture[5], char *path, int index)
{
    texture[index].img = mlx_xpm_file_to_image(vars->mlx_ptr, path, &texture[index].width, &texture[index].height);
    if (img.img == NULL)
        return (0);
    return (1);
}

void    ft_load_all_texture(t_vars *vars)
{
    t_img   texture[5];

    ft_load_texture(vars, texture, vars->cub->east_texture, 0);
    ft_load_texture(vars, texture, vars->cub->west_texture, 1);
    ft_load_texture(vars, texture, vars->cub->north_texture, 2);
    ft_load_texture(vars, texture, vars->cub->south_texture, 3);
    vars->texture = texture;
    ft_screen_exit(vars);
}
