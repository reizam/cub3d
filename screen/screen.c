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
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int line_height;
    int stepX;
    int stepY;
    int hit;
    int side;
    int x;

    x = 0;
    hit = 0;
    ft_draw_ground(vars);
    ft_draw_roof(vars);
    while (x < vars->cub->width)
    {
        cameraX = 2 * x / (double)vars->cub->width - 1;
        rayDirX = vars->dirX + vars->planeX * cameraX;
        rayDirY = vars->dirY + vars->planeY * cameraX;

        mapX = (int)vars->posX;
        mapY = (int)vars->posY;

        deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
        deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (vars->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (vars->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
        }
        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
                
            if (mapX >= 0 && mapY >= 0 && vars->cub->map[mapY][mapX] && vars->cub->map[mapY][mapX] == '1')
                hit = 1;
            if (mapX < 0 || mapY < 0 || !vars->cub->map[mapY][mapX])
                break ;
        }
        if (!hit)
            continue ;
        // -1 1 OUEST
        // 1 -1 EST
        // 1 1 SUD
        // -1 -1 NORD 
        if (side == 0)
            perpWallDist = (mapX - vars->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - vars->posY + (1 - stepY) / 2) / rayDirY;
        line_height = (int)(vars->cub->height / perpWallDist);
        int drawStart = -line_height / 2 + vars->cub->height / 2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = line_height / 2 + vars->cub->height / 2;
        if(drawEnd >= vars->cub->height)
            drawEnd = vars->cub->height - 1;
        double wallX;
        if (side == 0) wallX = vars->posY + perpWallDist * rayDirY;
        else           wallX = vars->posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));
        if (rayDirX == 1 && rayDirY == -1)
            side = 0;
        else if (rayDirX == 1 && rayDirY == -1)
            side = 1;
        else if (rayDirX == -1 && rayDirY == -1)
            side = 2;
        else if (rayDirX == 1 && rayDirY == 1)
            side = 3;
        t_img img = vars->textures[side];
        int texX = (int)(wallX * (double)img.width);
        if(side == 0 && rayDirX > 0) texX = img.width - texX - 1;
        if(side == 1 && rayDirY < 0) texX = img.width - texX - 1;
        ft_draw_ver_line_tex(vars, img, x, drawStart, drawEnd, line_height, texX);
        hit = 0;
        x++;
    }
    mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
    return (1);
}

void    ft_init_vars(t_vars *vars, t_cub *cub)
{
    vars->posX = cub->spawnX;
    vars->posY = cub->spawnY;
    vars->addr = NULL;
    vars->mlx_ptr = NULL;
    vars->win_ptr = NULL;
    vars->img_ptr = NULL;
    vars->dirX = -1;
    vars->dirY = 0;
    vars->planeX = 0;
    vars->planeY = 0.66;
    vars->time = 0;
    vars->old_time = 0;
    vars->move_speed = 0.3;
    vars->rot_speed = 0.15;
    vars->bits_per_pixel = 0;
    vars->line_length = 0;
    vars->endian = 0;
    vars->cub = cub;
}

int   ft_resize_hook(t_vars *vars)
{
    (void)vars;
    return (1);
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
    ft_load_all_texture(vars);
    mlx_get_screen_size(vars->mlx_ptr, &width, &height);
    cub->width = cub->width > width ? width : cub->width;
    cub->height = cub->height > height ? height : cub->height;
    vars->win_ptr = mlx_new_window(vars->mlx_ptr, cub->width, cub->height, "Cub3d");
    vars->img_ptr = mlx_new_image(vars->mlx_ptr, vars->cub->width, vars->cub->height);
    vars->addr = mlx_get_data_addr(vars->img_ptr, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
    mlx_hook(vars->win_ptr, 2, 1L<<0, ft_key_hook, vars);
    mlx_hook(vars->win_ptr, 25, 1L<<18, ft_resize_hook, vars);
    mlx_hook(vars->win_ptr, 17, 1L<<17, ft_leave_hook, vars);
    mlx_do_key_autorepeaton(vars->mlx_ptr);
    mlx_loop_hook(vars->mlx_ptr, ft_render_screen, vars);
    mlx_loop(vars->mlx_ptr);
}
