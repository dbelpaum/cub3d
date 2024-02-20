/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:42:39 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/30 17:37:10 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	set_ptrs_null(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->map = NULL;
	data->win_ptr = NULL;
	data->cam.x = 0;
	data->cam.y = 0;
	data->plane.x = 0;
	data->plane.y = 0;
	data->player.x = 0;
	data->player.y = 0;
}
