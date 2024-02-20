/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:05:44 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/15 11:21:27 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	init_ray(t_ray *ray, t_data *d)
{
	ray->cell_x = (int)d->player.x;
	ray->cell_y = (int)d->player.y;
	ray->pos.x = d->player.x;
	ray->pos.y = d->player.y;
	if (ray->dir.x == 0)
		ray->ddst.x = 0xfffffff;
	else
		ray->ddst.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->ddst.y = 0xfffffff;
	else
		ray->ddst.y = fabs(1.0 / ray->dir.y);
	ray->hit = 0;
	init_raynorm(ray);
}

static void	ray_life(t_ray *r, t_data *d)
{
	while (r->hit == 0)
	{
		if (r->sdst.x < r->sdst.y)
		{
			r->sdst.x += r->ddst.x;
			r->cell_x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->sdst.y += r->ddst.y;
			r->cell_y += r->step.y;
			r->side = 1;
		}
		if (d->map[r->cell_y][r->cell_x] == '1')
			r->hit = 1;
	}
	ray_lifenorm(r);
}

void	draw_texture(t_data *d, t_ray *r, void *t, t_n1 *n)
{
	t_myimg	img;
	int		tx;
	int		ty;

	img.img_ptr = t;
	img.img_data = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.line_size, &img.endian);
	tx = (int)(r->hit_offset * 64);
	tx *= 4;
	ty = n->tpos;
	ty *= 256.0;
	d->screen.img_data[(n->dstart + n->i) * d->screen.line_size + n->x
		* d->screen.bpp / 8] = img.img_data[ty + tx];
	d->screen.img_data[(n->dstart + n->i) * d->screen.line_size + n->x
		* d->screen.bpp / 8 + 1] = img.img_data[ty + tx + 1];
	d->screen.img_data[(n->dstart + n->i) * d->screen.line_size + n->x
		* d->screen.bpp / 8 + 2] = img.img_data[ty + tx + 2];
	d->screen.img_data[(n->dstart + n->i) * d->screen.line_size + n->x
		* d->screen.bpp / 8 + 3] = img.img_data[ty + tx + 3];
}

static void	draw_line(int x, t_ray *ray, t_data *d, void *texture)
{
	int		height;
	t_n1	n;

	n.x = x;
	height = (int)(RES_Y / ray->len);
	n.dstart = -height / 2 + RES_Y / 2;
	if (n.dstart < 0)
		n.dstart = 0;
	n.dend = height / 2 + RES_Y / 2;
	if (n.dend >= RES_Y)
		n.dend = RES_Y - 1;
	n.i = -1;
	draw_top_norm(d, &n);
	n.i = RES_Y;
	draw_bot_norm(d, &n, n.dend);
	n.i = -1;
	n.step = 1.0 * 64 / height;
	n.texpos = (n.dstart - RES_Y / 2 + height / 2) * n.step;
	draw_texture_norm(d, &n, ray, texture);
}

void	draw_screen(t_data *d)
{
	int		stripe;
	double	cam_x;
	t_ray	ray;
	void	*texture;

	stripe = -1;
	while (++stripe < RES_X)
	{
		cam_x = 2 * stripe / (double)RES_X - 1;
		ray.dir.x = d->cam.x + d->plane.x * cam_x;
		ray.dir.y = d->cam.y + d->plane.y * cam_x;
		init_ray(&ray, d);
		ray_life(&ray, d);
		if (ray.side == 0)
			texture = d->we;
		else if (ray.side == 1)
			texture = d->no;
		else if (ray.side == 2)
			texture = d->ea;
		else if (ray.side == 3)
			texture = d->so;
		draw_line(stripe, &ray, d, texture);
	}
	draw_minimap(d, (int)d->player.x, (int)d->player.y);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->screen.img_ptr, 0, 0);
}
