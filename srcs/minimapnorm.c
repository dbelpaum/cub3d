/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapnorm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:24:45 by ayblin            #+#    #+#             */
/*   Updated: 2022/11/15 10:56:20 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_norm1(t_data *d, t_n2 *n)
{
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8 + 2] = 50;
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8 + 1] = 50;
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8] = 50;
}

void	draw_norm2(t_data *d, t_n2 *n)
{
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8 + 2] = d->f[0];
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8 + 1] = d->f[1];
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8] = d->f[2];
}

void	draw_norm3(t_data *d, t_n2 *n)
{
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8 + 2] = 237;
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8 + 1] = 237;
	d->screen.img_data[(n->y + n->i) * d->screen.line_size + (n->x + n->j)
		* d->screen.bpp / 8] = 237;
}
