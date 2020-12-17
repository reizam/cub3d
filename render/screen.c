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

int     ft_key_hook(int keycode, t_vars *vars)
{
    // if (keycode == 119)
    // else if (keycode == 97)
    // else if (keycode == 100)
    // else if (keycode == 115)
    // printf("%d\n", keycode);
    (void)vars;
    return (1);
}

void    ft_draw_line(t_vars *vars, int start_x, int start_y, int end_x, int end_y)
{
    int dx;
    int dy;
    int e;

    e = end_x - start_x;
    dx = e * 2;
    dy = (end_y - start_y) * 2;
    while (start_x < end_x)
    {
        mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, start_x, start_y, vars->cub->rgb_ground);
        start_x++;
        if ((e = e - dy) <= 0)
        {
            start_y+=;
            e += dx;
        }
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
    while (x < vars->cub->width)
    {
        cameraX = 2 * x / double(vars->cub->width) - 1;
        rayDirX = vars->dirX + vars->planeX * cameraX;
        rayDirY = vars->dirY + vars->planeY * cameraX;

        mapX = int(vars->posX);
        mapY = int(vars->posY);

        deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
        deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));

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
            if (vars->cub->map[mapX][mapY] && vars->cub->map[mapX][mapY] == '1')
                hit = 1;
        }
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
        ft_draw_line(vars, x, drawStart, x + 1, drawEnd);
        hit = 0;
        x++;
    }
    return (1);
}

void    ft_open_screen(t_cub *cub)
{
    t_vars    *vars;

    if (!(vars = (t_vars*)malloc(sizeof(t_vars))))
        return ;
    // INIT VARS
    vars->posX = 0;
    vars->posY = 0;
    vars->dirX = -1;
    vars->dirY = 0;
    vars->planeX = 0;
    vars->planeY = 0.66;
    vars->time = 0;
    vars->old_time = 0;
    vars->cub = cub;
    
    // INIT
    vars->mlx_ptr = mlx_init();
    vars->win_ptr = mlx_new_window(vars->mlx_ptr, cub->width, cub->height, "Cub3d");
    mlx_key_hook(vars->win_ptr, ft_key_hook, vars);
    mlx_loop_hook(vars->mlx_ptr, ft_render_screen, vars);
    mlx_loop(vars->mlx_ptr);
    
    // FREE
    free(vars->mlx_ptr);
    free(vars->win_ptr);
    free(vars);
}