/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_draw_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:30:47 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/14 14:09:27 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_ceiling_floor(t_data *data);

void	draw_ceiling_floor(t_data *data)
{
	int32_t	i;
	int32_t	j;

	i = 0;
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
