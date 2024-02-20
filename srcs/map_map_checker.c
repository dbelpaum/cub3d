/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_map_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:26:46 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/23 12:41:50 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	check_map_borders(char **map)
{
	int	i;
	int	map_len;

	map_len = ft_strstrlen(map) - 1;
	i = -1;
	while (map[0][++i])
		if (map[0][i] != '1')
			return (write(2, "Error\nMap is not closed with walls\n", 35), 0);
	i = -1;
	while (map[map_len][++i])
		if (map[map_len][i] != '1')
			return (write(2, "Error\nMap is not closed with walls\n", 35), 0);
	i = -1;
	map_len = ft_strlen(map[0]) - 1;
	while (map[++i])
		if (map[i][0] != '1' || map[i][map_len] != '1')
			return (write(2, "Error\nMap is not closed with walls\n", 35), 0);
	return (1);
}

static int	check_map_chars(char **map)
{
	int	i;
	int	j;
	int	start_flag;

	i = -1;
	start_flag = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(VALID_MAP_CHARS, map[i][j]))
				return (write(2, "Error\nUnknown characters found\n", 31), 0);
			if (ft_strchr("NSEW", map[i][j]))
				start_flag++;
		}
	}
	if (start_flag != 1)
		return (write(2, "Error\nToo many spawn points\n", 28), 0);
	return (1);
}

void	map_padding(char **map)
{
	int		map_len;
	int		i;
	char	*tmp;
	int		j;

	map_len = -1;
	i = -1;
	while (map[++i])
		if ((int)ft_strlen(map[i]) > map_len)
			map_len = ft_strlen(map[i]);
	i = -1;
	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) < map_len)
		{
			j = ft_strlen(map[i]);
			tmp = (char *)malloc(sizeof(char) * (map_len + 1));
			ft_strlcpy(tmp, map[i], ft_strlen(map[i]) + 1);
			while (j < map_len)
				tmp[j++] = '1';
			tmp[j] = 0;
			free(map[i]);
			map[i] = tmp;
		}
	}
}

char	**read_map(int fd)
{
	char	**map;
	char	*line;
	char	*content;
	int		started_reading_map;

	content = NULL;
	started_reading_map = 0;
	line = gnl(fd);
	while (line)
	{
		if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
		{
			content = ft_strjoin(content, line);
			started_reading_map = 1;
		}
		if (started_reading_map && line[0] == '\n')
			return (free(line), free(content),
				write(2, "Error\nFound empty line in map\n", 30), NULL);
		free(line);
		line = gnl(fd);
	}
	ft_strreplace(content, ' ', '1');
	map = ft_split(content, '\n');
	free(content);
	return (map);
}

int	is_valid_map(int fd)
{
	char	**map;

	map = read_map(fd);
	if (!map)
		return (0);
	map_padding(map);
	if (!check_map_chars(map) || !check_map_borders(map))
		return (0);
	free_strstr(map);
	return (1);
}
