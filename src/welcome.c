/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/17 18:08:10 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	welcome_screen(t_data *data);

void	welcome_screen(t_data *data)
{
	mlx_texture_t	*tex;
	int				pos_x;
	int				pos_y;
	int				x;
	int				y;

	tex = mlx_load_png("imgs/cube.png");
	if (!tex)
		exit_err(data, "Failed to load welcome texture", FAILURE);
	data->screen.background = mlx_new_image(data->mlx, data->mlx->width,
			data->mlx->height);
	y = -1;
	while (++y < data->mlx->height)
	{
		x = -1;
		while (++x < data->mlx->width)
			mlx_put_pixel(data->screen.background, x, y, 0x000000FF);
	}
	data->screen.welcome_img = mlx_texture_to_image(data->mlx, tex);
	pos_x = (data->mlx->width - tex->width) / 2;
	pos_y = (data->mlx->height - tex->height) / 2;
	mlx_image_to_window(data->mlx, data->screen.background, 0, 0);
	mlx_image_to_window(data->mlx, data->screen.welcome_img, pos_x, pos_y);
	data->screen.is_welcome = true;
	mlx_delete_texture(tex);
}
