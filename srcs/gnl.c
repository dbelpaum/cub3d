/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:35:31 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/21 20:02:08 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static char	*gnl_join(char *s1, char c)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < (int)ft_strlen(s1))
		res[i] = s1[i];
	res[ft_strlen(s1)] = c;
	res[ft_strlen(s1) + 1] = '\0';
	free(s1);
	return (res);
}

char	*gnl(int fd)
{
	char	buffer;
	char	*line;
	int		nb_read;

	line = (char *)malloc(sizeof(char));
	line[0] = 0;
	nb_read = read(fd, &buffer, 1);
	if (nb_read <= 0)
		return (free(line), NULL);
	while (nb_read > 0)
	{
		line = gnl_join(line, buffer);
		if (buffer == '\n' || (nb_read <= 0 && ft_strlen(line) > 0))
			return (line);
		nb_read = read(fd, &buffer, 1);
	}
	if (buffer == '\n' || (nb_read <= 0 && ft_strlen(line) > 0))
		return (line);
	return (NULL);
}
