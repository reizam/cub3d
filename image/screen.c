/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:00:54 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/25 18:00:54 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_render_screen(t_vars *vars)
{
	int i;

	i = -1;
	if (!vars->h_buffer)
		if (!(vars->h_buffer = (double*)malloc(sizeof(double)
		* (vars->cub->width + 1))))
			return (0);
	while (++i < vars->cub->width + 1)
		vars->h_buffer[i] = 0;
	ft_draw_ground(vars);
	ft_draw_roof(vars);
	ft_draw_wall(vars, &vars->h_buffer);
	ft_draw_sprite(vars, vars->h_buffer);
	ft_do_controls(vars);
	if (!vars->cub->save_first_image)
		mlx_put_image_to_window(vars->mlx_ptr,
		vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}

void	ft_init_vars(t_vars *vars, t_cub *cub)
{
	vars->pos_x = cub->spawn_x + 0.5;
	vars->pos_y = cub->spawn_y + 0.5;
	vars->addr = NULL;
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
	vars->textures[4].img_ptr = NULL;
	vars->h_buffer = NULL;
	vars->keys[0] = 0;
	vars->keys[1] = 0;
	vars->keys[2] = 0;
	vars->keys[3] = 0;
	vars->cub = cub;
}

int		ft_leave_hook(t_vars *vars)
{
	ft_screen_exit(vars);
	return (1);
}

void	ft_save_first_image(t_cub *cub, t_vars *vars)
{
	if (cub->save_first_image)
	{
		ft_render_screen(vars);
		ft_save_image(vars, "game_screen.bmp");
		ft_screen_exit(vars);
	}
}

void	ft_open_screen(t_cub *cub)
{
	t_vars	*vars;
	int		width;
	int		height;

	if (!(vars = (t_vars*)malloc(sizeof(t_vars))))
		return ;
	ft_init_vars(vars, cub);
	vars->mlx_ptr = mlx_init();
	if (!ft_load_all_texture(vars))
		ft_screen_init_exit(vars, 1);
	mlx_get_screen_size(vars->mlx_ptr, &width, &height);
	cub->width = cub->width > width ? width : cub->width;
	cub->height = cub->height > height ? height : cub->height;
	vars->img_ptr = mlx_new_image(vars->mlx_ptr,
	vars->cub->width, vars->cub->height);
	vars->addr = mlx_get_data_addr(vars->img_ptr,
	&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	ft_save_first_image(cub, vars);
	vars->win_ptr = mlx_new_window(vars->mlx_ptr,
	cub->width, cub->height, "Cub3d");
	mlx_hook(vars->win_ptr, 2, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->win_ptr, 3, 1L << 1, ft_key_release, vars);
	mlx_hook(vars->win_ptr, 33, 1L << 17, ft_leave_hook, vars);
	mlx_loop_hook(vars->mlx_ptr, ft_render_screen, vars);
	mlx_loop(vars->mlx_ptr);
}
