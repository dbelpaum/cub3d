/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:01:59 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/14 14:29:31 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	free_data(t_data *data)
{
	if (data->map)
		free_strstr(data->map);
	if (data->no)
		mlx_destroy_image(data->mlx_ptr, data->no);
	if (data->so)
		mlx_destroy_image(data->mlx_ptr, data->so);
	if (data->we)
		mlx_destroy_image(data->mlx_ptr, data->we);
	if (data->ea)
		mlx_destroy_image(data->mlx_ptr, data->ea);
	if (data->screen.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->screen.img_ptr);
	if (data->mlx_ptr && data->win_ptr)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
	}
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	free(data);
}
