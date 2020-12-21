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
    double  i[8];
    int     j[5];
    int line_height;
    int hit;
    int x;

    x = 0;
    hit = 0;
    ft_draw_ground(vars);
    ft_draw_roof(vars);
    while (x < vars->cub->width)
    {
        i[0] = 2 * x / (double)vars->cub->width - 1;
        i[1] = vars->dirX + vars->planeX * i[0];
        i[2] = vars->dirY + vars->planeY * i[0];
        j[0] = (int)vars->posX;
        j[1] = (int)vars->posY;
        i[3] = (i[2] == 0) ? 0 : ((i[1] == 0) ? 1 : fabs(1 / i[1]));
        i[4] = (i[1] == 0) ? 0 : ((i[2] == 0) ? 1 : fabs(1 / i[2]));
        if (i[1] < 0)
        {
            j[2] = -1;
            i[5] = (vars->posX - j[0]) * i[3];
        }
        else
        {
            j[2] = 1;
            i[5] = (j[0] + 1.0 - vars->posX) * i[3];
        }
        if (i[2] < 0)
        {
            j[3] = -1;
            i[6] = (vars->posY - j[1]) * i[4];
        }
        else
        {
            j[3] = 1;
            i[6] = (j[1] + 1.0 - vars->posY) * i[4];
        }
        while (!hit)
        {
            if (i[5] < i[6])
            {
                i[5] += i[3];
                j[0] += j[2];
                j[4] = 0;
            }
            else
            {
                i[6] += i[4];
                j[1] += j[3];
                j[4] = 1;
            }
            if (j[0] >= 0 && j[1] >= 0 && vars->cub->map[j[1]][j[0]] && vars->cub->map[j[1]][j[0]] == '1')
                hit = 1;
            if (j[0] < 0 || j[1] < 0 || !vars->cub->map[j[1]][j[0]])
                break ;
        }
        if (!hit)
            continue ;
        i[7] = j[4] == 0 ? ((j[0] - vars->posX + (1 - j[2]) / 2) / i[1]) : ((j[1] - vars->posY + (1 - j[3]) / 2) / i[2]);
        line_height = (int)(vars->cub->height / i[7]);
        int drawStart = -line_height / 2 + vars->cub->height / 2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = line_height / 2 + vars->cub->height / 2;
        if(drawEnd >= vars->cub->height)
            drawEnd = vars->cub->height - 1;
        double wallX;
        wallX = j[4] == 0 ? (vars->posY + i[7] * i[2]) : (wallX = vars->posX + i[7] * i[1]);
        wallX -= floor((wallX));
        if (j[4] == 0)
            j[4] = j[2] > 0 ? 0 : 1;
        else
            j[4] = j[3] > 0 ? 2 : 3;
        t_img img = vars->textures[j[4]];
        int texX = (int)(wallX * (double)img.width);
        texX = img.width - texX - 1;
        ft_draw_texture_line(vars, img, x, drawStart, drawEnd, line_height, texX);
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
    vars->move_speed = 0.3;
    vars->rot_speed = 0.15;
    vars->bits_per_pixel = 0;
    vars->line_length = 0;
    vars->endian = 0;
    vars->textures[0].img_ptr = NULL;
    vars->textures[1].img_ptr = NULL;
    vars->textures[2].img_ptr = NULL;
    vars->textures[3].img_ptr = NULL;
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
    if(!ft_load_all_texture(vars))
        ft_screen_init_exit(vars, 1);
    mlx_get_screen_size(vars->mlx_ptr, &width, &height);
    cub->width = cub->width > width ? width : cub->width;
    cub->height = cub->height > height ? height : cub->height;
    vars->img_ptr = mlx_new_image(vars->mlx_ptr, vars->cub->width, vars->cub->height);
    vars->win_ptr = mlx_new_window(vars->mlx_ptr, cub->width, cub->height, "Cub3d");
    vars->addr = mlx_get_data_addr(vars->img_ptr, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
    mlx_hook(vars->win_ptr, 2, 1L<<0, ft_key_hook, vars);
    mlx_hook(vars->win_ptr, 25, 1L<<0, ft_resize_hook, vars);
    mlx_hook(vars->win_ptr, 17, 1L<<0, ft_leave_hook, vars);
    mlx_do_key_autorepeaton(vars->mlx_ptr);
    mlx_loop_hook(vars->mlx_ptr, ft_render_screen, vars);
    mlx_loop(vars->mlx_ptr);
}
