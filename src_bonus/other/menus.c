/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/04/01 19:38:05 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void		welcome_screen(t_data *data, char *path);
static void	draw_background(t_data *data);
mlx_image_t	*scale_image(mlx_t *mlx, mlx_texture_t *texture, int win_width,
				int win_height);
static void	process_pixels(mlx_image_t *scaled_image, mlx_texture_t *texture,
				float scale);

void	welcome_screen(t_data *data, char *path)
{
	int			pos_x;
	int			pos_y;
	mlx_image_t	*scaled_image;
	int			scaled_width;
	int			scaled_height;

	draw_background(data);
	data->screen.tex = mlx_load_png(path);
	if (!data->screen.tex)
		exit_err(data, "Failed to load screen texture", FAILURE);
	scaled_image = scale_image(data->mlx, data->screen.tex, data->mlx->width,
			data->mlx->height);
	if (scaled_image == NULL)
		exit_err(data, "Failed to scale the screen img", FAILURE);
	data->screen.welcome_img = scaled_image;
	scaled_width = data->screen.welcome_img->width;
	scaled_height = data->screen.welcome_img->height;
	data->screen.orig_w = scaled_width;
	data->screen.orig_h = scaled_height;
	pos_x = (data->mlx->width - scaled_width) / 2;
	pos_y = (data->mlx->height - scaled_height) / 2;
	mlx_image_to_window(data->mlx, data->screen.welcome_img, pos_x, pos_y);
	data->screen.is_welcome = true;
}

static void	draw_background(t_data *data)
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
	mlx_image_to_window(data->mlx, data->screen.background, 0, 0);
}

mlx_image_t	*scale_image(mlx_t *mlx, mlx_texture_t *texture, int win_width,
		int win_height)
{
	mlx_image_t	*scaled_image;
	float		scale;
	int			new_width;
	int			new_height;

	scale = fmin(((float)win_width / texture->width / 2), ((float)win_height
				/ texture->height / 2));
	new_width = (int)(texture->width * scale);
	new_height = (int)(texture->height * scale);
	scaled_image = mlx_new_image(mlx, new_width, new_height);
	if (!scaled_image)
		return (NULL);
	process_pixels(scaled_image, texture, scale);
	return (scaled_image);
}

static void	process_pixels(mlx_image_t *scaled_image, mlx_texture_t *texture,
		float scale)
{
	unsigned int	x;
	unsigned int	y;
	int				raw_color;
	int				color;

	y = 0;
	while (y < scaled_image->height)
	{
		x = 0;
		while (x < scaled_image->width)
		{
			raw_color = ((int *)texture->pixels)[((int)(y / scale))
				* texture->width + ((int)(x / scale))];
			color = ((raw_color & 0xFF) << 24) 
				| ((raw_color & 0xFF00) << 8) 
				| ((raw_color & 0xFF0000) >> 8) 
				| ((raw_color & 0xFF000000) >> 24);
			mlx_put_pixel(scaled_image, x, y, color);
			x++;
		}
		y++;
	}
}
