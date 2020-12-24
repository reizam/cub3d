/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:47:47 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/24 14:47:47 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_sprite    *ft_create_elem()
{
    t_sprite *elem;

    if (!(elem = (t_sprite)malloc(sizeof(t_sprite))))
        return (NULL);
    return (elem);
}

void	ft_lstadd_front(t_sprite **alst, int x, int y)
{
    t_sprite *new_elem;

    if (!(new_elem = ft_create_elem()))
        return ;
	if ((*alst) != NULL)
		new_elem->next = (*alst);
    new_elem->x = x;
    new_elem->y = y;
	(*alst) = new_elem;
}

double  ft_distance(int pos_x, int pos_y, int sprite_x, int sprite_y)
{
    return (((pos_x - sprite_x) * (pos_x - sprite_x) + (pos_y - sprite_y) * (pos_y - sprite_y)));
}

void    ft_sort_sprites(t_sprite *begin, int pos_x, int pos_y)
{
    int         temp;
    t_sprite    *cpy;

    cpy = begin;
    while (begin)
    {
        if (begin->next && ft_distance(pos_x, pos_y, begin->x, begin->y) > ft_distance(pos_x, pos_y, begin->next->x, begin->next->y))
        {
            temp = begin->x;
            begin->x = begin->next->x;
            begin->next->x = temp;
            temp = begin->y;
            begin->y = begin->next->y;
            begin->next->y = temp;
            begin = cpy;
        }
        begin = begin->next;
    }
}

void	ft_lstclear(t_sprite **lst)
{
	t_sprite *next;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst));
		(*lst) = NULL;
		(*lst) = next;
	}
	lst = NULL;
}