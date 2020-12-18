/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:20:06 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 18:01:06 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    ft_check_file_ext(char *file, char *extension)
{
    int     i;
    int     len;

    len = ft_strlen(file);
    i = ft_strlen(extension);
    if (len <= i)
        return (0);
    while (i > 0)
    {
        if (extension[i - 1] != file[len - (4 - i) - 1])
            return (0);
        i--;
    }
    return (1);
}

int		ft_nb_len(int nb)
{
	int i;

	i = 1;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int		ft_is_full(t_cub *cub)
{
	return (cub->height != 0 && cub->width != 0 && cub->sprite_texture != NULL
    && cub->north_texture != NULL && cub->east_texture != NULL
    && cub->west_texture != NULL && cub->south_texture != NULL
    && cub->rgb_ground != -1
    && cub->rgb_roof != -1);
}

int     ft_isnum(char *str)
{
    int i;
    
    i = -1;
    while (str[++i])
        if (str[i] < '0' || str[i] > '9')
            return (0);
    return (1);
}
