/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:10:22 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/17 23:01:24 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2, int n)
{
	char			*result;
	size_t			i;
	size_t			j;

	i = (s1 == NULL ? 0 : ft_strlen((char*)s1))
	+ (s2 == NULL ? 0 : ft_strlen((char*)s2));
	if (!(result = (char*)malloc((i + 1 + n) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		result[i++] = s2[j++];
    if (n == 1)
        result[i++] = '\n';
	result[i] = 0;
	if (s1)
		free(s1);
	return (result);
}
