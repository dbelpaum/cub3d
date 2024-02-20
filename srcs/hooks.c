/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:49:09 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/15 10:51:52 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	camera_move(int keycode, t_data *d)
{
	double	old_cam;
	double	old_plane;

	old_cam = d->cam.x;
	old_plane = d->plane.x;
	if (keycode == RIGHT_ARROW)
	{
		d->cam.x = d->cam.x * cos(-CAM_STEP) - d->cam.y * sin(-CAM_STEP);
		d->cam.y = old_cam * sin(-CAM_STEP) + d->cam.y * cos(-CAM_STEP);
		d->plane.x = d->plane.x * cos(-CAM_STEP) - d->plane.y * sin(-CAM_STEP);
		d->plane.y = old_plane * sin(-CAM_STEP) + d->plane.y * cos(-CAM_STEP);
	}
	else
	{
		d->cam.x = d->cam.x * cos(CAM_STEP) - d->cam.y * sin(CAM_STEP);
		d->cam.y = old_cam * sin(CAM_STEP) + d->cam.y * cos(CAM_STEP);
		d->plane.x = d->plane.x * cos(CAM_STEP) - d->plane.y * sin(CAM_STEP);
		d->plane.y = old_plane * sin(CAM_STEP) + d->plane.y * cos(CAM_STEP);
	}
}

static void	player_move_horizontal(int keycode, t_data *d)
{
	t_vect	tmp;

	if (keycode == LEFT_KEY)
	{
		tmp.x = d->cam.y;
		tmp.y = -d->cam.x;
		if (d->map[(int)d->player.y][(int)(d->player.x + tmp.x * STEP)] == 48)
			d->player.x += tmp.x * STEP;
		if (d->map[(int)(d->player.y + tmp.y * STEP)][(int)d->player.x] == 48)
			d->player.y += tmp.y * STEP;
	}
	if (keycode == RIGHT_KEY)
	{
		tmp.x = -d->cam.y;
		tmp.y = d->cam.x;
		if (d->map[(int)d->player.y][(int)(d->player.x + tmp.x * STEP)] == 48)
			d->player.x += tmp.x * STEP;
		if (d->map[(int)(d->player.y + tmp.y * STEP)][(int)d->player.x] == 48)
			d->player.y += tmp.y * STEP;
	}
}

static void	player_move_vertical(int keycode, t_data *d)
{
	if (keycode == UP_KEY)
	{
		if (d->map[(int)d->player.y][(int)(d->player.x + d->cam.x * STEP)]
		== 48)
			d->player.x += d->cam.x * STEP;
		if (d->map[(int)(d->player.y + d->cam.y * STEP)][(int)d->player.x]
		== 48)
			d->player.y += d->cam.y * STEP;
	}
	else
	{
		if (d->map[(int)d->player.y][(int)(d->player.x - d->cam.x * STEP)]
		== 48)
			d->player.x -= d->cam.x * STEP;
		if (d->map[(int)(d->player.y - d->cam.y * STEP)][(int)d->player.x]
		== 48)
			d->player.y -= d->cam.y * STEP;
	}
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		free_data(data);
		printf("You exited the game\n");
		exit(0);
	}
	else if (keycode == UP_KEY || keycode == DOWN_KEY)
		player_move_vertical(keycode, data);
	else if (keycode == RIGHT_KEY || keycode == LEFT_KEY)
		player_move_horizontal(keycode, data);
	else if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
		camera_move(keycode, data);
	if (keycode == UP_KEY || keycode == DOWN_KEY || keycode == RIGHT_KEY
		|| keycode == LEFT_KEY || keycode == LEFT_ARROW || keycode == 65361)
		draw_screen(data);
	return (0);
}

int	mouse_hook(int x, int y, t_data *data)
{
	if (x < 320)
	{
		camera_move_mouse(RIGHT_ARROW, data);
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, 320, 220);
		draw_screen(data);
	}
	else if (x > 320)
	{
		camera_move_mouse(LEFT_ARROW, data);
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, 320, 220);
		draw_screen(data);
	}
	(void)x;
	(void)y;
	return (0);
}
