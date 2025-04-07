/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_draw_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:30:47 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/07 13:30:20 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void		draw_ceiling_floor(t_data *data);
static void	default_clrs(t_data *data);

void	draw_ceiling_floor(t_data *data)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	default_clrs(data);
	while (i < data->mlx->height / 2)
	{
		j = 0;
		while (j < data->mlx->width)
		{
			mlx_put_pixel(data->img, j, i, data->input.sky);
			j++;
		}
		i++;
	}
	while (i < data->mlx->height)
	{
		j = 0;
		while (j < data->mlx->width)
		{
			mlx_put_pixel(data->img, j, i, data->input.floor);
			j++;
		}
		i++;
	}
}

// sets default colors if needed
static void	default_clrs(t_data *data)
{
	if (data->input.floor == -1)
		data->input.floor = CLR_FLOOR;
	if (data->input.sky == -1)
		data->input.sky = CLR_SKY;
}
