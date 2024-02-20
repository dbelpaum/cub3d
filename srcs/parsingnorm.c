/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingnorm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:49:09 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/13 21:02:21 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	*xpm_to_image_norm(t_data *d, char	*l)
{
	int		res;

	res = SPR_RES;
	return (mlx_xpm_file_to_image(d->mlx_ptr,
			ft_strrchr(l, ' ') + 1, &res, &res));
}

void	init_data_norm(t_data *data, int nb)
{
	if (nb == 1)
	{
		data->cam.y = -1;
		data->plane.x = CAMERA_FOV;
	}
	if (nb == 2)
	{
		data->cam.x = 1;
		data->plane.y = CAMERA_FOV;
	}
	if (nb == 3)
	{
		data->cam.y = 1;
		data->plane.x = -CAMERA_FOV;
	}
	if (nb == 4)
	{
		data->cam.x = -1;
		data->plane.y = -CAMERA_FOV;
	}
}
