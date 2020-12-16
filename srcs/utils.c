/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:20:06 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 18:01:06 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int    ft_is_cub_file(char *file)
{
    char    *end;
    int     i;
    int     len;

    end = ".cub";
    len = ft_strlen(file);
    i = 4;
    if (len <= 4)
        return (0);
    while (i > 0)
    {
        if (end[i - 1] != file[len - i - 1])
            return (0);
        i--;
    }
    return (1);
}

int		ft_nb_len(int nb)
{
	int i;

	i = 1;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void    free_cub(t_cub *cub)
{
    // TODO:
}

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}