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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char*)s;
	while (i < n)
	{
		str[i] = (char)c;
		i++;
	}
	return ((void*)str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (!(result = (void*)malloc(nmemb * size)))
		return (NULL);
	ft_memset(result, 0, nmemb * size);
	return (result);
}

unsigned char *ft_create_bmp_file_header(t_vars *vars, int pitch)
{
    unsigned char   *file_header;
    int             file_size;
  
    file_header = (unsigned char*)ft_calloc(sizeof(unsigned char), 14);
    file_size = 54 + (pitch + ((4 - pitch % 4) % 4)) * vars->cub->height;
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

    info_header = (unsigned char*)ft_calloc(sizeof(unsigned char), 40);
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
    info_header[14] = (unsigned char)(vars->bits_per_pixel * 8);
    return (info_header);
}

void    ft_save_image(t_vars *vars, char *file_name)
{
    unsigned char   *info_header;
    unsigned char   *file_header;
    unsigned char   padding[3];
    unsigned char   *cpy;
    int             fd;
    int             pitch;
    int             i;

    i = -1;
    cpy = (unsigned char*)vars->addr;
    pitch = vars->bits_per_pixel * vars->cub->width;
    info_header = ft_create_bmp_file_header(vars, pitch);
    file_header = ft_create_bmp_info_header(vars);
    fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
    write(fd, file_header, 14);
    write(fd, info_header, 40);
    while (++i < vars->cub->height)
    {
        write(fd, cpy + (i * pitch), vars->bits_per_pixel * vars->cub->width);
        write(fd, padding, (4 - pitch % 4) % 4);
    }
    close(fd);
}