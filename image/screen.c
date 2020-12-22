/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:37:37 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/16 17:37:37 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_draw_ground(t_vars *vars)
{
    int x;
    int y;

    y = vars->cub->height / 2 - 1;
    while (++y < vars->cub->height - 1)
    {
        x = -1;
        while (++x < vars->cub->width - 1)
            ft_draw_pixel(vars, x, y, vars->cub->rgb_ground);
    }
}

void    ft_draw_roof(t_vars *vars)
{
    int x;
    int y;

    y = -1;
    while (++y < vars->cub->height / 2 - 1)
    {
        x = -1;
        while (++x < vars->cub->width - 1)
            ft_draw_pixel(vars, x, y, vars->cub->rgb_roof);
    }
}

int     ft_render_screen(t_vars *vars)
{
    ft_draw_ground(vars);
    ft_draw_roof(vars);
    ft_draw_wall(vars);
    ft_do_controls(vars);
    if (!vars->cub->save_first_image)
        mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
    else

    return (1);
}

void    ft_init_vars(t_vars *vars, t_cub *cub)
{
    vars->pos_x = cub->spawn_x;
    vars->pos_y = cub->spawn_y;
    vars->addr = NULL;
    vars->mlx_ptr = NULL;
    vars->win_ptr = NULL;
    vars->img_ptr = NULL;
    vars->dir_x = cub->dir_x;
    vars->dir_y = cub->dir_y;
    vars->plane_x = cub->plane_x;
    vars->plane_y = cub->plane_y;
    vars->move_speed = 0.15;
    vars->rot_speed = 0.07;
    vars->bits_per_pixel = 0;
    vars->line_length = 0;
    vars->endian = 0;
    vars->textures[0].img_ptr = NULL;
    vars->textures[1].img_ptr = NULL;
    vars->textures[2].img_ptr = NULL;
    vars->textures[3].img_ptr = NULL;
    vars->keys[0] = 0;
    vars->keys[1] = 0;
    vars->keys[2] = 0;
    vars->keys[3] = 0;
    vars->cub = cub;
}

int   ft_leave_hook(t_vars *vars)
{
    ft_screen_exit(vars);
    return (1);
}

void    ft_open_screen(t_cub *cub)
{
    t_vars  *vars;
    int     width;
    int     height;

    if (!(vars = (t_vars*)malloc(sizeof(t_vars))))
        return ;
    ft_init_vars(vars, cub);
    vars->mlx_ptr = mlx_init();
    if(!ft_load_all_texture(vars))
        ft_screen_init_exit(vars, 1);
    mlx_get_screen_size(vars->mlx_ptr, &width, &height);
    cub->width = cub->width > width ? width : cub->width;
    cub->height = cub->height > height ? height : cub->height;
    vars->img_ptr = mlx_new_image(vars->mlx_ptr, vars->cub->width, vars->cub->height);
    if (cub->save_first_image)
    {
        ft_render_screen(vars);
        ft_save_image(vars, "first_image.bmp");
        ft_screen_exit(vars);
    }
    vars->addr = mlx_get_data_addr(vars->img_ptr, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
    vars->win_ptr = mlx_new_window(vars->mlx_ptr, cub->width, cub->height, "Cub3d");
    mlx_hook(vars->win_ptr, 2, 1L<<0, ft_key_press, vars);
    mlx_hook(vars->win_ptr, 3, 1L<<1, ft_key_release, vars);
    mlx_hook(vars->win_ptr, 17, 1L<<17, ft_leave_hook, vars);
    mlx_loop_hook(vars->mlx_ptr, ft_render_screen, vars);
    mlx_loop(vars->mlx_ptr);
}
