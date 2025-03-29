/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/29 17:45:58 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void		welcome_screen(t_data *data, char *path);
void		menu_clean(t_data *data);
static void	draw_background(t_data *data);
mlx_image_t	*scale_image(mlx_t *mlx, mlx_texture_t *texture, int win_width,
				int win_height);

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
	// data->screen.welcome_img = mlx_texture_to_image(data->mlx,
	// data->screen.tex);
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

	printf("background\n");
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
	float		scale_x;
	float		scale_y;
	int			new_width;
	int			new_height;
	mlx_image_t	*scaled_image;
	int			src_x;
	int			src_y;
	float		scale;
	int			raw_color;
	int			color;

	scale_x = (float)win_width / texture->width / 2;
	scale_y = (float)win_height / texture->height / 2;
	scale = fmin(scale_x, scale_y);
	new_width = (int)(texture->width * scale);
	new_height = (int)(texture->height * scale);
	scaled_image = mlx_new_image(mlx, new_width, new_height);
	if (!scaled_image)
		return (NULL);
	for (int y = 0; y < new_height; ++y)
	{
		for (int x = 0; x < new_width; ++x)
		{
			src_x = (int)(x / scale);
			src_y = (int)(y / scale);
			raw_color = ((int *)texture->pixels)[src_y * texture->width
				+ src_x];
			color = ((raw_color & 0xFF) << 24) | ((raw_color & 0xFF00) << 8) | ((raw_color & 0xFF0000) >> 8) | ((raw_color & 0xFF000000) >> 24);
			mlx_put_pixel(scaled_image, x, y, color);
		}
	}
	return (scaled_image);
}

void	clean_menus(t_data *data)
{
	if (data->screen.background)
	{
		mlx_delete_image(data->mlx, data->screen.background);
		data->screen.background = NULL;
	}
	if (data->screen.welcome_img)
	{
		mlx_delete_image(data->mlx, data->screen.welcome_img);
		data->screen.welcome_img = NULL;
	}
	if (data->screen.tex)
	{
		mlx_delete_texture(data->screen.tex);
		data->screen.tex = NULL;
	}
}
