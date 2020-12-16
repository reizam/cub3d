/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:03:49 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 18:20:18 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_print_error(char *error)
{
    ft_putstr_fd("Error\n", 0);
    ft_putstr_fd(error, 0);
    ft_putstr_fd("\n", 0);
}

int     start_cub3d(int ac, char **av)
{
    t_cub *cub;

    if (!ft_is_cub_file(av[1]))
    {
        ft_print_error("Wrong file type.")
        return (0);
    }
    if (ac == 3)
        if (ft_strcmp(av[2], "--save") != 0)
        {
            ft_print_error("Wrong arguments.");
            return (0);
        }
        else
            cub->save_first_image = 1;
    if (!(cub = ft_parse_cub_file(av[1])))
    {
        ft_print_error("Wrong config.");
        return (0);
    }
    return (1);
}

int main (int ac, char **av)
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