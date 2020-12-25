/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:01:41 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/25 18:01:41 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_ground(t_vars *vars)
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

void	ft_draw_roof(t_vars *vars)
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
