/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:50:20 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/15 10:56:05 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	draw_square(int x, int y, t_data *d, char c)
{
	t_n2	n;

	n.c = c;
	n.y = y;
	n.x = x;
	n.i = -1;
	while (++n.i < 8)
	{
		n.j = -1;
		while (++n.j < 8)
		{
			if (n.c == '1')
			{
				draw_norm1(d, &n);
			}
			if (n.c == '0')
			{
				draw_norm2(d, &n);
			}
			if (n.c == 'P')
			{
				draw_norm3(d, &n);
			}
		}
	}
}

void	draw_minimap(t_data *d, int px, int py)
{
	int	i;

	if (!d->print_minimap)
		return ;
	i = -1;
	while (++i < d->map_width * d->map_height)
	{
		if (i % d->map_width == px && i / d->map_width == py)
			draw_square(32 +(i % d->map_width) * 8, 32 +(i / d->map_width) * 8,
				d, 'P');
		else
			draw_square(32 +(i % d->map_width) * 8, 32 +(i / d->map_width) * 8,
				d, d->map[i / d->map_width][i % d->map_width]);
	}
}
