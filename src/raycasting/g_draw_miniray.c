/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_draw_miniray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:37:40 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/10 23:44:25 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_miniray(t_data *data, t_ray *ray)
{
	t_coord	p1;
	t_coord	p2;
	t_coord	delta;
	float	step;
	int		i;

	p1.x = data->player.x;
	p1.y = data->player.y;
	p2.x = p1.x + ray->cos_angle * ray->distance * TILE_SIZE;
	p2.y = p1.y - ray->sin_angle * ray->distance * TILE_SIZE;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	step = fmaxf(fabsf(delta.x), fabsf(delta.y));
	delta.x /= step;
	delta.y /= step;
	i = 0;
	while (i <= step)
	{
		mlx_put_pixel(data->img, (int)rint(p1.x), (int)rint(p1.y), RAY_COL);
		p1.x += delta.x;
		p1.y += delta.y;
		i++;
	}
}
