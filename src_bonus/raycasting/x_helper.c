/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:06:11 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/01 19:19:34 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

float	deg_to_rad(int nb);
float	rad_to_deg(float nb);
void	put_pixel_minimap(t_data *data, int x, int y, uint32_t color);

float	deg_to_rad(int nb)
{
	return (nb * (2 * M_PI) / 360.0);
}

float	rad_to_deg(float nb)
{
	return (nb * 180.0 / (M_PI));
}

void	put_pixel_minimap(t_data *data, int x, int y, uint32_t color)
{
	if (x > OFFSET && y > OFFSET && x < (PLAYER_X - OFFSET) * 2 && y < (PLAYER_Y
			- OFFSET) * 2 && x < data->mlx->width && y < data->mlx->height)
		mlx_put_pixel(data->img, x, y, color);
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
