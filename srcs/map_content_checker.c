/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:28:25 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/22 21:19:59 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	valid_texture_l(char *l)
{
	int	i;

	i = 0;
	while (l[i] != ' ')
		i++;
	while (l[i] == ' ')
		i++;
	while (l[i] != ' ' && l[i] != '\n')
		i++;
	if (l[i] != '\n')
		return (0);
	return (1);
}

static int	valid_fc_l(char *l)
{
	int	i;

	i = 1;
	while (l[i] && l[i] == ' ')
		i++;
	if (!ft_isdigit(l[i]) || ft_atoi(l + i) < 0 || ft_atoi(l + i) > 255)
		return (0);
	while (l[i] && l[i] != ',')
		i++;
	if (!ft_isdigit(l[i + 1])
		|| ft_atoi(l + i + 1) < 0 || ft_atoi(l + i + 1) > 255)
		return (0);
	while (l[i] && l[++i] != ',')
		;
	if (!ft_isdigit(l[i + 1])
		|| ft_atoi(l + i + 1) < 0 || ft_atoi(l + i + 1) > 255)
		return (0);
	i++;
	while (l[i] && ft_isdigit(l[i]))
		i++;
	if (l[i] != '\n')
		return (0);
	return (1);
}

static int	check_line(char *l)
{
	if (ft_strlen(l) < 4)
		return (-1);
	if (l[0] == 'N' && l[1] == 'O' && l[2] == ' ' && valid_texture_l(l))
		return (0);
	else if (l[0] == 'S' && l[1] == 'O' && l[2] == ' ' && valid_texture_l(l))
		return (1);
	else if (l[0] == 'W' && l[1] == 'E' && l[2] == ' ' && valid_texture_l(l))
		return (2);
	else if (l[0] == 'E' && l[1] == 'A' && l[2] == ' ' && valid_texture_l(l))
		return (3);
	else if (l[0] == 'F' && l[1] == ' ' && valid_fc_l(l))
		return (4);
	else if (l[0] == 'C' && l[1] == ' ' && valid_fc_l(l))
		return (5);
	else
		return (-1);
}

int	is_valid_file_content(int fd)
{
	static int	flags[6] = {0};
	char		*line;
	int			flag_id;

	line = gnl(fd);
	while (line && line[0] != ' ' && line[0] != '1')
	{
		if (ft_strncmp(line, "\n", 2) != 0)
		{
			flag_id = check_line(line);
			if (flag_id == -1)
				return (free(line), 0);
			flags[flag_id]++;
		}
		free(line);
		line = gnl(fd);
	}
	free(line);
	flag_id = -1;
	while (++flag_id < 6)
		if (flags[flag_id] != 1)
			return (0);
	return (1);
}
