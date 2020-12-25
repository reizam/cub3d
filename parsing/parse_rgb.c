/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   parse_rgb.c										:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2020/12/16 08:26:30 by marvin			#+#	#+#			          */
/*   Updated: 2020/12/16 08:26:30 by marvin		   ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "cub3d.h"

int	 ft_check_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	 ft_free_splitted_str(char **s)
{
	int i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	if (s)
		free(s);
	return (0);
}

int	 ft_parse_rgb(char *line, int id, t_cub *cub)
{
	char	**s;
	int	 i;
	int	 r;
	int	 g;
	int	 b;

	s = ft_split(line, ',');
	i = 0;
	cub->error = "Wrong RGB parameter...";
	while (s && s[i])
		i++;
	if (!s || i != 3)
		return (ft_free_splitted_str(s));
	if (!ft_isnum(s[0]) || !ft_isnum(s[1]) || !ft_isnum(s[2]))
		return (ft_free_splitted_str(s));
	r = ft_atoi(s[0]);
	g = ft_atoi(s[1]);
	b = ft_atoi(s[2]);
	i = 0;
	ft_free_splitted_str(s);
	if (!ft_check_rgb(r, g, b))
		return (0);
	if (id == 0)
		cub->rgb_ground = (0 << 24 | r << 16 | g << 8 | b);
	else if (id == 1)
		cub->rgb_roof = (0 << 24 | r << 16 | g << 8 | b);
	return (1);
}
