/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:59:06 by ayblin            #+#    #+#             */
/*   Updated: 2022/11/15 10:52:03 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	camera_move_mouse(int keycode, t_data *d)
{
	double	old_cam;
	double	old_plane;

	old_cam = d->cam.x;
	old_plane = d->plane.x;
	if (keycode == RIGHT_ARROW)
	{
		d->cam.x = d->cam.x * cos(-MSE_STEP) - d->cam.y * sin(-MSE_STEP);
		d->cam.y = old_cam * sin(-MSE_STEP) + d->cam.y * cos(-MSE_STEP);
		d->plane.x = d->plane.x * cos(-MSE_STEP) - d->plane.y * sin(-MSE_STEP);
		d->plane.y = old_plane * sin(-MSE_STEP) + d->plane.y * cos(-MSE_STEP);
	}
	else
	{
		d->cam.x = d->cam.x * cos(MSE_STEP) - d->cam.y * sin(MSE_STEP);
		d->cam.y = old_cam * sin(MSE_STEP) + d->cam.y * cos(MSE_STEP);
		d->plane.x = d->plane.x * cos(MSE_STEP) - d->plane.y * sin(MSE_STEP);
		d->plane.y = old_plane * sin(MSE_STEP) + d->plane.y * cos(MSE_STEP);
	}
}

int	red_cross_exit(t_data *data)
{
	free_data(data);
	printf("You exited the game\n");
	exit(0);
}
