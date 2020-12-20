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

int     ft_load_texture(t_vars *vars, t_img textures[5], char *path, int index)
{
    textures[index].img = mlx_xpm_file_to_image(vars->mlx_ptr, path, &textures[index].width, &textures[index].height);
    if (textures[index].img == NULL)
        return (0);
    return (1);
}

void    ft_load_all_texture(t_vars *vars)
{
    t_img   textures[5];

    ft_load_texture(vars, textures, vars->cub->east_texture, 0);
    ft_load_texture(vars, textures, vars->cub->west_texture, 1);
    ft_load_texture(vars, textures, vars->cub->north_texture, 2);
    ft_load_texture(vars, textures, vars->cub->south_texture, 3);
    vars->textures = textures;
}
