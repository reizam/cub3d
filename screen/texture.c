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

int ft_load_texture(t_vars *vars, t_img textures[5], char *path, int index)
{
    textures[index].img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, path, &textures[index].width, &textures[index].height);
    if (textures[index].img_ptr == NULL)
        return (0);
    textures[index].addr = (int*)mlx_get_data_addr(textures[index].img_ptr, &textures[index].bits_per_pixel, &textures[index].line_length, &textures[index].endian);
    return (1);
}

int ft_load_all_texture(t_vars *vars)
{
    if (!ft_load_texture(vars, vars->textures, vars->cub->east_texture, 0))
        return (0);
    if (!ft_load_texture(vars, vars->textures, vars->cub->west_texture, 1))
        return (0);
    if (!ft_load_texture(vars, vars->textures, vars->cub->north_texture, 2))
        return (0);
    if (!ft_load_texture(vars, vars->textures, vars->cub->south_texture, 3))
        return (0);
    return (1);
}
