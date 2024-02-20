/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:16:09 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/14 14:28:36 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	get_rgb(int fd, t_data *data)
{
	char	*l;
	char	**tmp;

	l = gnl(fd);
	while (l)
	{
		if (ft_strlen(l) > 7 && ft_strncmp(l, "F ", 2) == 0)
		{
			tmp = ft_split(ft_strrchr(l, ' ') + 1, ',');
			data->f[0] = ft_atoi(tmp[0]);
			data->f[1] = ft_atoi(tmp[1]);
			data->f[2] = ft_atoi(tmp[2]);
			free_strstr(tmp);
		}
		if (ft_strlen(l) > 7 && ft_strncmp(l, "C ", 2) == 0)
		{
			tmp = ft_split(ft_strrchr(l, ' ') + 1, ',');
			data->c[0] = ft_atoi(tmp[0]);
			data->c[1] = ft_atoi(tmp[1]);
			data->c[2] = ft_atoi(tmp[2]);
			free_strstr(tmp);
		}
		free(l);
		l = gnl(fd);
	}
}

static void	get_textures(int fd, t_data *d)
{
	char	*l;

	d->screen.img_ptr = NULL;
	l = gnl(fd);
	while (l)
	{
		ft_strreplace(l, '\n', 0);
		if (ft_strlen(l) > 8 && l[0] == 'N' && l[1] == 'O')
			d->no = xpm_to_image_norm(d, l);
		else if (ft_strlen(l) > 8 && l[0] == 'S' && l[1] == 'O')
			d->so = xpm_to_image_norm(d, l);
		else if (ft_strlen(l) > 8 && l[0] == 'W' && l[1] == 'E')
			d->we = xpm_to_image_norm(d, l);
		else if (ft_strlen(l) > 8 && l[0] == 'E' && l[1] == 'A')
			d->ea = xpm_to_image_norm(d, l);
		free(l);
		l = gnl(fd);
	}
	if (!d->no || !d->so || !d->we || !d->ea)
	{
		free_data(d);
		exit(write(2, "Error: Invalid texture path\n", 28));
	}
	close(fd);
}

static void	init_data2(t_data *data)
{
	int	i;

	data->map_height = ft_strstrlen(data->map);
	data->map_width = ft_strlen(data->map[0]);
	i = -1;
	while (++i < data->map_height * data->map_width)
	{
		if (ft_strchr("NSWE",
				data->map[i / data->map_width][i % data->map_width]))
		{
			data->player.x = i % data->map_width + 0.5;
			data->player.y = i / data->map_width + 0.5;
			if (data->map[i / data->map_width][i % data->map_width] == 'N')
				init_data_norm(data, 1);
			else if (data->map[i / data->map_width][i % data->map_width] == 'E')
				init_data_norm(data, 2);
			else if (data->map[i / data->map_width][i % data->map_width] == 'S')
				init_data_norm(data, 3);
			else if (data->map[i / data->map_width][i % data->map_width] == 'W')
				init_data_norm(data, 4);
			data->map[i / data->map_width][i % data->map_width] = '0';
		}
	}
}

static t_data	*init_data(char *filename)
{
	t_data	*data;
	int		fd;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
	set_ptrs_null(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (free(data), ft_putstr_fd("Error: mlx_init failed\n", 2), NULL);
	data->win_ptr = mlx_new_window(data->mlx_ptr, RES_X, RES_Y, "cub3D");
	fd = open(filename, O_RDONLY);
	get_textures(fd, data);
	fd = open(filename, O_RDONLY);
	get_rgb(fd, data);
	close(fd);
	fd = open(filename, O_RDONLY);
	data->map = read_map(fd);
	close(fd);
	map_padding(data->map);
	if (!data->mlx_ptr || !data->win_ptr || !data->no || !data->so || !data->we
		|| !data->ea || !data->map)
		return (free_data(data), write(2, "Error: sprites\n", 15), NULL);
	init_data2(data);
	return (data);
}

t_data	*parse_map(char *filename)
{
	int		len;
	int		fd;

	len = ft_strlen(filename);
	if (len < 5 || !ft_strnstr(filename + len - 4, ".cub", 4))
		return (ft_putstr_fd("Error: unknown file format\n", 2), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (perror("open"), NULL);
	if (!is_valid_file_content(fd))
		return (NULL);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (perror("open"), NULL);
	if (!is_valid_map(fd))
		return (NULL);
	close(fd);
	return (init_data(filename));
}
