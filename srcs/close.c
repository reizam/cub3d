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

t_cub *parse_exit(t_cub *cub)
{
    int         i;

    i = 0;
    if (!cub)
        return (NULL);
    if (cub->east_texture)
        free(cub->south_texture);
    if (cub->east_texture)
        free(cub->west_texture);
    if (cub->east_texture)
        free(cub->east_texture);
    if (cub->east_texture)
        free(cub->north_texture);
    if (cub->east_texture)
        free(cub->sprite_texture);
    if (map)
    {
        while (map[i])
            free(map[i++]);
        free(map);
    }
    free(cub);
    return (NULL);
}