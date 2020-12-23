/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:08:49 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/22 22:08:49 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char *ft_create_bmp_file_header(t_vars *vars, int pitch)
{
    unsigned char   *file_header;
    int             file_size;
    int             i;

    i = -1;
    file_header = (unsigned char*)malloc(sizeof(unsigned char) * 14);
    while (++i <= 14)
        file_header[i] = 0;
    file_size = 54 + ((pitch) + (4 - (pitch) % 4) % 4)) * vars->cub->height;
    file_header[0] = (unsigned char)('B');
    file_header[1] = (unsigned char)('M');
    file_header[2] = (unsigned char)(file_size);
    file_header[3] = (unsigned char)(file_size >> 8);
    file_header[4] = (unsigned char)(file_size >> 16);
    file_header[5] = (unsigned char)(file_size >> 24);
    file_header[10] = (unsigned char)(54);
    return (file_header);
}


unsigned char *ft_create_bmp_info_header(t_vars *vars)
{
    unsigned char *info_header;
    int             i;

    i = -1;
    if (!info_header = (unsigned char*)malloc(sizeof(unsigned char) * 40))
        return (NULL);
    while (++i <= 40)
        info_header[i] = 0;
    info_header[0] = (unsigned char)(40);
    info_header[4] = (unsigned char)(vars->cub->width);
    info_header[5] = (unsigned char)(vars->cub->width >> 8);
    info_header[6] = (unsigned char)(vars->cub->width >> 16);
    info_header[7] = (unsigned char)(vars->cub->width >> 24);
    info_header[8] = (unsigned char)(vars->cub->height);
    info_header[9] = (unsigned char)(vars->cub->height >> 8);
    info_header[10] = (unsigned char)(vars->cub->height >> 16);
    info_header[11] = (unsigned char)(vars->cub->height >> 24);
    info_header[12] = (unsigned char)(1);
    info_header[14] = (unsigned char)(vars->bits_per_pixel);
    return (info_header);
}

void    ft_save_image(t_vars *vars, char *file_name)
{
    unsigned char   *info_header;
    unsigned char   *file_header;
    unsigned char   *cpy;
    int             fd;
    int             pitch;
    int             i;
    int             j;
    static unsigned char rgb[3] = {0, 0, 0};
    i = -1;
    cpy = (unsigned char*)vars->addr;
    pitch = (vars->bits_per_pixel / 8) * vars->cub->width;
    info_header = ft_create_bmp_file_header(vars, pitch);
    file_header = ft_create_bmp_info_header(vars);
    fd = open(file_name, O_WRONLY | O_CREAT, 0777);
    write(fd, file_header, 14);
    write(fd, info_header, 40);
    while (++i < vars->cub->height)
    {
        j = -1;
        while (++j < vars->cub->width)
        {
            rgb[0] = cpy[(vars->cub->height - i) * (vars->cub->width) + j] >> 16;
            rgb[1] = cpy[(vars->cub->height - i) * (vars->cub->width) + j] >> 8;
            rgb[2] = cpy[(vars->cub->height - i) * (vars->cub->width) + j] >> 16;
            write(fd, rgb + 2, 1);
            write(fd, rgb + 1, 1);
            write(fd, rgb, 1);
        }
    }
    free(info_header);
    free(file_header);
    close(fd);
}