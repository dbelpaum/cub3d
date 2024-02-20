/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:20:06 by ayblin            #+#    #+#             */
/*   Updated: 2022/11/15 11:23:06 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_raynorm(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sdst.x = (ray->pos.x - ray->cell_x) * ray->ddst.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sdst.x = (ray->cell_x + 1 - ray->pos.x) * ray->ddst.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sdst.y = (ray->pos.y - ray->cell_y) * ray->ddst.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sdst.y = (ray->cell_y + 1 - ray->pos.y) * ray->ddst.y;
	}
}

void	ray_lifenorm(t_ray *r)
{
	if (r->side == 0)
		r->len = r->sdst.x - r->ddst.x;
	else
		r->len = r->sdst.y - r->ddst.y;
	if (r->side == 0)
	{
		r->hit_offset = r->pos.y + r->len * r->dir.y;
		if (r->cell_x > r->pos.x)
			r->side = 2;
	}
	else
	{
		r->hit_offset = r->pos.x + r->len * r->dir.x;
		if (r->cell_y > r->pos.y)
			r->side = 3;
	}
	r->hit_offset = r->hit_offset - (int)r->hit_offset;
}

void	draw_top_norm(t_data *d, t_n1 *n)
{
	while (++n->i < n->dstart)
	{
		if (d->print_minimap && n->x >= 32 && n->x <= 32 + 8 * d->map_width
			&& n->i >= 32 && n->i < 32 + 8 * d->map_height)
			continue ;
		d->screen.img_data[n->i * d->screen.line_size + n->x
			* d->screen.bpp / 8 + 2] = d->c[0];
		d->screen.img_data[n->i * d->screen.line_size + n->x
			* d->screen.bpp / 8 + 1] = d->c[1];
		d->screen.img_data[n->i * d->screen.line_size + n->x
			* d->screen.bpp / 8] = d->c[2];
	}
}

void	draw_bot_norm(t_data *d, t_n1 *n, int dend)
{
	while (--n->i > dend)
	{
		if (d->print_minimap && n->x >= 32 && n->x <= 32 + 8 * d->map_width
			&& n->i >= 32 && n->i < 32 + 8 * d->map_height)
			continue ;
		d->screen.img_data[n->i * d->screen.line_size + n->x
			* d->screen.bpp / 8 + 2] = d->f[0];
		d->screen.img_data[n->i * d->screen.line_size + n->x
			* d->screen.bpp / 8 + 1] = d->f[1];
		d->screen.img_data[n->i * d->screen.line_size + n->x
			* d->screen.bpp / 8] = d->f[2];
	}
}

void	draw_texture_norm(t_data *d, t_n1 *n, t_ray *ray, void *texture)
{
	while (++n->i <= n->dend - n->dstart)
	{
		n->texpos += n->step;
		n->tpos = (int)n->texpos & 63;
		if (d->print_minimap && n->x >= 32 && n->x <= 32 + 8 * d->map_width
			&& n->i + n->dstart >= 32 && n->i
			+ n->dstart < 32 + 8 * d->map_height)
			continue ;
		draw_texture(d, ray, texture, n);
	}
}
