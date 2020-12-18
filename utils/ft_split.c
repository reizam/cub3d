/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:00:40 by kmazier           #+#    #+#             */
/*   Updated: 2020/12/15 13:33:43 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	ft_getsplitsize(char const *s, char c)
{
	size_t i;
	size_t j;
	size_t size;

	i = 0;
	j = 0;
	size = 1;
	while (s && s[i])
	{
		j = 0;
		while (s && s[i + j] && s[i + j] != c)
			j++;
		if (j)
		{
			size++;
			i += j;
		}
		else
			i++;
	}
	return (size);
}

static char		*ft_allocate_entry(char const *s, size_t start, size_t end)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * ((end - start) + 1))))
		return (NULL);
	while (s[start] && start < end)
		result[i++] = s[start++];
	result[i] = 0;
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (!(result = (char**)malloc(sizeof(char*) * ft_getsplitsize(s, c))))
		return (NULL);
	while (s && s[i])
	{
		j = 0;
		while (s && s[i + j] && s[i + j] != c)
			j++;
		if (j)
		{
			if (!(result[k++] = ft_allocate_entry(s, i, i + j)))
				return (NULL);
			i += j;
		}
		else
			i++;
	}
	result[k] = 0;
	return (result);
}
