/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:37:01 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/25 18:37:01 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_vars *vars, int dir)
{
	if (vars->cub->map[(int)vars->pos_y][(int)(vars->pos_x
	 + (dir * (vars->dir_x * vars->move_speed)))] != '1')
		vars->pos_x += dir * (vars->dir_x * vars->move_speed);
	if (vars->cub->map[(int)(vars->pos_y +(dir *
	(vars->dir_y * vars->move_speed)))][(int)vars->pos_x] != '1')
		vars->pos_y += dir * (vars->dir_y * vars->move_speed);
}

void	ft_rot(t_vars *vars, int dir)
{
	double temp;

	temp = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rot_speed * dir)
	- vars->dir_y * sin(vars->rot_speed * dir);
	vars->dir_y = temp * sin(vars->rot_speed * dir)
	+ vars->dir_y * cos(vars->rot_speed * dir);
	temp = vars->plane_x;
	vars->plane_x = vars->plane_x * cos(vars->rot_speed * dir)
	- vars->plane_y * sin(vars->rot_speed * dir);
	vars->plane_y = temp * sin(vars->rot_speed * dir)
	+ vars->plane_y * cos(vars->rot_speed * dir);
}

void	ft_do_controls(t_vars *vars)
{
	if (vars->keys[0])
		ft_move(vars, 1);
	else if (vars->keys[1])
		ft_move(vars, -1);
	if (vars->keys[2])
		ft_rot(vars, 1);
	else if (vars->keys[3])
		ft_rot(vars, -1);
}

int		ft_key_press(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->keys[0] = 1;
	else if (keycode == S_KEY)
		vars->keys[1] = 1;
	else if (keycode == A_KEY)
		vars->keys[2] = 1;
	else if (keycode == D_KEY)
		vars->keys[3] = 1;
	else if (keycode == ESC_KEY)
		ft_screen_exit(vars);
	return (1);
}

int		ft_key_release(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->keys[0] = 0;
	else if (keycode == S_KEY)
		vars-> keys[1] = 0;
	else if (keycode == A_KEY)
		vars->keys[2] = 0;
	else if (keycode == D_KEY)
		vars->keys[3] = 0;
	return (1);
}
