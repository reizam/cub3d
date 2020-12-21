/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:47:34 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/18 16:47:34 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_draw_wall_line(t_vars *vars, int x, int j[5], double i[8])
{
    int     k[4];
    double  wall_x;
    t_img   img;
    
    k[2] = (int)(vars->cub->height / i[7]);
    k[0] = -k[2] / 2 + vars->cub->height / 2;
    k[0] = k[0] < 0 ? 0 : k[0];
    k[1] = k[2] / 2 + vars->cub->height / 2;
    k[1] = k[1] >= vars->cub->height ? vars->cub->height - 1 : k[1];
    wall_x = j[4] == 0 ? (vars->posY + i[7] * i[2]) : (vars->posX + i[7] * i[1]);
    wall_x -= floor((wall_x));
    if (j[4] == 0)
        j[4] = j[2] > 0 ? 0 : 1;
    else
        j[4] = j[3] > 0 ? 2 : 3;
    img = vars->textures[j[4]];
    k[3] = (int)(wall_x * (double)img.width);
    k[3] = img.width - k[3] - 1;
    ft_draw_texture_line(vars, img, x, k);
}

void    ft_calc_side_dist(double (*i)[8], int (*j)[5])
{
    if ((*i)[1] < 0)
    {
        (*j)[2] = -1;
        (*i)[5] = (vars->posX - (*j)[0]) * (*j)[3];
    }
    else
    {
        (*j)[2] = 1;
        (*i)[5] = (*j[0] + 1.0 - vars->posX) * (*i)[3];
    }
    if ((*i)[2] < 0)
    {
        (*j)[3] = -1;
        (*i)[6] = (vars->posY - *j[1]) * (*i)[4];
    }
    else
    {
        (*j)[3] = 1;
        (*i)[6] = ((*j)[1] + 1.0 - vars->posY) * (*i)[4];
    }
}

int     ft_raycast(t_vars *vars, double (*i)[8], int (*j)[5])
{
    while (1)
    {
        if ((*i)[5] < (*i)[6])
        {
            (*i)[5] += (*i)[3];
            (*j)[0] += (*j)[2];
            (*j)[4] = 0;
        }
        else
        {
            (*i)[6] += (*i)[4];
            (*j)[1] += (*j)[3];
            (*j)[4] = 1;
        }
        if ((*j)[0] >= 0 && (*j)[1] >= 0 && vars->cub->map[(*j)[1]][(*j)[0]i] && vars->cub->map[(*j)[1]][(*j)[0]] == '1')
            return (1);
        if ((*j)[0] < 0 || (*j)[1] < 0 || !vars->cub->map[(*j)[1]][(*j)[0]])
            break ;
    }
    return (0);
}

void    ft_draw_wall(t_vars *vars)
{
    double  i[8];
    int     j[5];
    int     x;

    x = -1;
    while (++x < vars->cub->width)
    {
        i[0] = 2 * x / (double)vars->cub->width - 1;
        i[1] = vars->dirX + vars->planeX * i[0];
        i[2] = vars->dirY + vars->planeY * i[0];
        j[0] = (int)vars->posX;
        j[1] = (int)vars->posY;
        i[3] = (i[2] == 0) ? 0 : ((i[1] == 0) ? 1 : fabs(1 / i[1]));
        i[4] = (i[1] == 0) ? 0 : ((i[2] == 0) ? 1 : fabs(1 / i[2]));
        ft_calc_side_dist(&i, &j);
        if (!ft_raycast(&i, &j))
            continue ;
        i[7] = j[4] == 0 ? ((j[0] - vars->posX + (1 - j[2]) / 2) / i[1]) : ((j[1] - vars->posY + (1 - j[3]) / 2) / i[2]);
        ft_draw_wall_line(vars, x, j, i);
        hit = 0;
    }
}