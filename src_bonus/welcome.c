/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/25 19:11:15 by htharrau         ###   ########.fr       */
=======
/*   Updated: 2025/03/25 15:55:36 by ilazar           ###   ########.fr       */
>>>>>>> inbar
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void		welcome_screen(t_data *data, char *path);
static void	draw_background(t_data *data);

void	welcome_screen(t_data *data , char *path)
{
	int	pos_x;
	int	pos_y;

	data->screen.tex = mlx_load_png(path);
	if (!data->screen.tex)
		exit_err(data, "Failed to load screen texture", FAILURE);
	draw_background(data);
	data->screen.welcome_img = mlx_texture_to_image(data->mlx,
			data->screen.tex);
	data->screen.orig_w = data->screen.welcome_img->width;
	data->screen.orig_h = data->screen.welcome_img->height;
	pos_x = (data->mlx->width - data->screen.tex->width) / 2;
	pos_y = (data->mlx->height - data->screen.tex->height) / 2;
	mlx_image_to_window(data->mlx, data->screen.background, 0, 0);
	mlx_image_to_window(data->mlx, data->screen.welcome_img, pos_x, pos_y);
	data->screen.is_welcome = true;
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	data->screen.background = mlx_new_image(data->mlx, data->mlx->width,
			data->mlx->height);
	y = -1;
	while (++y < data->mlx->height)
	{
		x = -1;
		while (++x < data->mlx->width)
			mlx_put_pixel(data->screen.background, x, y, 0x000000FF);
	}
}
