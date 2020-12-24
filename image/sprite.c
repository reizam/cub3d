/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:29:42 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/22 21:29:42 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_draw_sprite(t_vars *vars, double *h_buffer)
{
    t_sprite *sprite;
    t_img   sprite_img;

    sprite = vars->cub->sprite;
    sprite_img = vars->textures[4];
    ft_sort_sprites(&sprite, vars->pos_x, vars->pos_y);
    while (sprite)
    {
        double sprite_x = sprite->x - vars->pos_x;
        double sprite_y = sprite->y - vars->pos_y;

        double inv_vet = 1.0 / (vars->plane_x * vars->dir_y - vars->dir_x * vars->plane_y);

        double transform_x = inv_vet * (vars->dir_y * sprite_x - vars->dir_x * sprite_y);
        double transform_y = inv_vet * (-vars->plane_y * sprite_x + vars->plane_x * sprite_y);

        int sprite_screen_x = (int)((vars->cub->width / 2) * (1 + transform_x / transform_y));

        int sprite_height = abs((int)(vars->cub->height / (transform_y)));

        int drawStartY = -sprite_height / 2 + vars->cub->height / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = sprite_height / 2 + vars->cub->height / 2;
        if(drawEndY >= vars->cub->height) drawEndY = vars->cub->height - 1;

        int sprite_width = abs((int)(vars->cub->height / transform_y));

        int drawStartX = -sprite_width / 2 + sprite_screen_x;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = sprite_width / 2 + sprite_screen_x;
        if(drawEndX >= vars->cub->width) drawEndX = vars->cub->width - 1;
    
        int stripe = drawStartX - 1;
        while (++stripe < drawEndX)
        {
            int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * sprite_img.width / sprite_img.width) / 256);
            
            int y = drawStartY - 1;
            if(transform_y > 0 && stripe > 0 && stripe < vars->cub->width && transform_y < h_buffer[stripe])
                while (++y < drawEndY)
                {
                    int d = (y) * 256 - vars->cub->height * 128 + sprite_height * 128;
                    int tex_y = ((d * sprite_img.height) / sprite_height) / 256;
                    ft_draw_pixel_if_not_black(vars, stripe, y, sprite_img.addr[sprite_img.width * tex_y + tex_x]);
                }
        }
        sprite = sprite->next;
    }
}