/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:45:39 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/30 17:58:01 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	debug_print_vectors(t_data *data)
{
	printf("\nVectors:\nPLANE:(%f | %f)\nPLAYER:(%f | %f)\nCAM:(%f | %f)\n",
		data->plane.x, data->plane.y, data->player.x, data->player.y,
		data->cam.x, data->cam.y);
}

void	debug_print_data(t_data *data)
{
	int	i;

	printf("mlx ptrs :\nWIN:%p\nMLX:%p\nNO:%p\nSO:%p\nWE:%p\nEA:%p\n\n",
		data->win_ptr, data->mlx_ptr, data->no, data->so, data->we, data->ea);
	printf("rgb values:\nF[%d,%d,%d]\nC[%d,%d,%d]\n\n",
		data->f[0], data->f[1], data->f[2], data->c[0], data->c[1], data->c[2]);
	printf("map:\n");
	i = -1;
	while (data->map[++i])
		printf("%s\n", data->map[i]);
	printf("\n%dx%d\n", data->map_width, data->map_height);
	debug_print_vectors(data);
}
