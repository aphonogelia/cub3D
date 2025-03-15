/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_resize_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:32:23 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/15 17:40:51 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
/* 
void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	(void)width;
	(void)height;
	data = (t_data *)param;
	data->flag_refresh = true;
} */

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->screen.is_welcome)
	{
		mlx_resize_image(data->screen.background, width, height);
		data->screen.welcome_img->instances[0].x = \
		(width - data->screen.welcome_img->width) / 2;
		data->screen.welcome_img->instances[0].y = \
		(height - data->screen.welcome_img->height) / 2;
	}
	else
		data->flag_refresh = true;
}
