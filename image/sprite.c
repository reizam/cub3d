/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:59:21 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/25 17:59:21 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_sprite_texture(t_vars *vars, int i[12], double d[5], double *h_buffer)
{
	t_img   sprite_img;
	int		y;

	sprite_img = vars->textures[4];
	i[2] = -i[1] / 2 + vars->cub->height / 2;
	i[2] = i[2] < 0 ? 0 : i[2];
	i[3] = i[1] / 2 + vars->cub->height / 2;
	i[3] = i[3] >= vars->cub->height ? vars->cub->height - 1 : i[3];
	i[4] = abs((int)(vars->cub->height / d[4]));
	i[5] = -i[4] / 2 + i[0];
	i[5] = i[5] < 0 ? 0 : i[5];
	i[6] = i[4] / 2 + i[0];
	i[6] = i[6] >= vars->cub->width ? vars->cub->width - 1 : i[6];
	i[8] = i[5] - 1;
	while (++i[8] < i[6])
	{
		i[9] = (int)((256 * (i[8] - (-i[4] / 2 + i[0]))
		* sprite_img.width / i[4]) / 256);
		y = i[2] - 1;
		if (d[4] > 0 && i[8] > 0 &&
		i[8] < vars->cub->width && d[4] < h_buffer[i[8]])
			while (++y < i[3])
			{
				i[10] = (y) * 256 - vars->cub->height * 128 + i[1] * 128;
				i[11] = ((i[10] * sprite_img.height) / i[1]) / 256;
				ft_draw_pixel_if_not_black(vars, i[8], y, sprite_img.addr[sprite_img.width * i[11] + i[9]]);
			}
	}
}

void	ft_draw_sprite(t_vars *vars, double *h_buffer)
{
	t_sprite	*sprite;
	double		d[5];
	int			i[12];

	sprite = vars->cub->sprite;
	ft_sort_sprites(&sprite, vars->pos_x, vars->pos_y);
	while (sprite)
	{
		d[0] = sprite->x - vars->pos_x;
		d[1] = sprite->y - vars->pos_y;
		d[2] = 1.0 / (vars->plane_x * vars->dir_y
		- vars->dir_x * vars->plane_y);
		d[3] = d[2] * (vars->dir_y * d[0] - vars->dir_x * d[1]);
		d[4] = d[2] * (-vars->plane_y * d[0] + vars->plane_x * d[1]);
		i[0] = (int)((vars->cub->width / 2) * (1 + d[3] / d[4]));
		i[1] = abs((int)(vars->cub->height / (d[4])));
		ft_draw_sprite_texture(vars, i, d, h_buffer);
		sprite = sprite->next;
	}
}
