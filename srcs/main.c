/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 00:06:51 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/11/15 11:26:02 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (ft_putstr_fd("usage: ./cub3D <map.cub>\n", 2), 1);
	data = parse_map(av[1]);
	if (!data)
		return (write(2, "Could not parse map\n", 20), 1);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win_ptr, 17, (0L), red_cross_exit, data);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_hook, data);
	data->screen.img_ptr = mlx_new_image(data->mlx_ptr, RES_X, RES_Y);
	data->screen.img_data = mlx_get_data_addr(data->screen.img_ptr,
			&data->screen.bpp, &data->screen.line_size, &data->screen.endian);
	if (data->map_width > MAX_WIDTH || data->map_height > MAX_HEIGHT)
		data->print_minimap = 0;
	else
		data->print_minimap = 1;
	draw_screen(data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (0);
}
