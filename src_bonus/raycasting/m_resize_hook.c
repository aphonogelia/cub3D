/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_resize_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:32:23 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/26 17:37:59 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void			resize_hook(int32_t width, int32_t height, void *param);
static float	calc_scale(t_data *data, int32_t width, int32_t height);
static void		gameplay_screen(t_data *data, int32_t width, int32_t height);

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data		*data;
	uint32_t	new_w;
	uint32_t	new_h;
	float		scale;

	data = (t_data *)param;
	if (data->screen.is_welcome)
	{
		mlx_resize_image(data->screen.background, width, height);
		scale = calc_scale(data, width, height);
		new_w = data->screen.orig_w * scale;
		new_h = data->screen.orig_h * scale;
		mlx_delete_image(data->mlx, data->screen.welcome_img);
		if (!data->screen.welcome_img)
			exit_err(data, "Failed to load welcome screen during resizing",
				FAILURE);
		data->screen.welcome_img = mlx_texture_to_image(data->mlx,
				data->screen.tex);
		mlx_resize_image(data->screen.welcome_img, new_w, new_h);
		mlx_image_to_window(data->mlx, data->screen.welcome_img, (width - new_w)
			/ 2, (height - new_h) / 2);
	}
	else
		gameplay_screen(data, width, height);
}

// calculate the ratio scale of the resizable image
static float	calc_scale(t_data *data, int32_t width, int32_t height)
{
	float	scale;
	float	width_ratio;
	float	height_ratio;

	scale = 1.0f;
	if (width < data->screen.orig_w || height < data->screen.orig_h)
	{
		width_ratio = (float)width / data->screen.orig_w;
		height_ratio = (float)height / data->screen.orig_h;
		scale = height_ratio;
		if (width_ratio < height_ratio)
			scale = width_ratio;
	}
	return (scale);
}

static void	gameplay_screen(t_data *data, int32_t width, int32_t height)
{
	data->mlx->width = width;
	data->mlx->height = height;
	data->flag_refresh = true;
}
