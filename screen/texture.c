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

int     ft_load_texture(t_vars *vars, char *path, int index)
{
    t_img   *img;

    if (!(img = (*t_img)malloc(sizeof(t_img))))
        return (0);
    img->img = mlx_xpm_file_to_image(vars->mlx_ptr, path, &img->width, &img->height);
    if (img == NULL)
        return (0);
    vars->textures[index] = img;
    return (1);
}

void    ft_load_all_texture(t_vars *vars)
{
    ft_load_texture(vars, vars->cub->east_texture, 0);
    ft_load_texture(vars, vars->cub->west_texture, 1);
    ft_load_texture(vars, vars->cub->north_texture, 2);
    ft_load_texture(vars, vars->cub->south_texture, 3);
    ft_screen_exit(vars);
}
