/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:03:25 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 18:01:13 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_cub
{
    int         save_first_image;
    int         height;
    int         width;
    char        *south_texture;
    char        *west_texture;
    char        *east_texture;
    char        *north_texture;
    char        *sprite_texture;
    int         **map;
}	            t_cub;

int     ft_is_map_char(char c);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int     ft_strcmp(char *s1, char *s2);
int     ft_strncmp(char *s1, char *s2, size_t n);
int     ft_is_cub_file(char *file_name);
int		get_next_line(int fd, char **line);
void    free_cub(t_cub *cub);
int     ft_check_line(char *line);
int     **parse_map(char *line, int fd, t_cub *cub);
int		ft_nb_len(int nb);

#endif