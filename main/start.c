/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:52:32 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/25 17:52:32 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_error(char *error)
{
	if (ft_strlen(error) == 0)
		return ;
	ft_putstr_fd("Error\n", 0);
	ft_putstr_fd(error, 0);
	ft_putstr_fd("\n", 0);
}

int		start_cub3d(int ac, char **av)
{
	t_cub *cub;

	if (!ft_check_file_ext(av[1], ".cub"))
	{
		ft_print_error("Wrong file type.");
		return (0);
	}
	if (ac == 3)
	{
		ft_print_error("Too many arguments.");
		return (0);
	}
	if (!(cub = ft_parse_cub_file(av[1])))
		return (0);
	if (ac == 4)
	{
		if (ft_strcmp(av[2], "--save") != 0 && !ft_check_file_ext(av[3], ".bmp"))
		{
			cub->error = "Wrong arguments.";
			ft_parse_exit(cub);
			return (0);
		}
		cub->save_first_image = av[3];
	}
	ft_open_screen(cub);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac == 3 || ac == 2)
	{
		if (!start_cub3d(ac, av))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
