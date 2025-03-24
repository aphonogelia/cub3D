/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_draw_miniray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:37:40 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/24 17:29:17 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void		draw_miniray(t_data *data, int u);
void		save_miniray(t_data *data, t_ray *ray, int u);
static void	draw_horizontal(t_data *data, t_coord *p1, t_coord *p2);
static void	draw_vertical(t_data *data, t_coord *p1, t_coord *p2);
static void	draw_line(t_data *data, t_coord *p1, t_coord *delta);

void	save_miniray(t_data *data, t_ray *ray, int u)
{
	data->miniray[u].distance = ray->distance;
	data->miniray[u].cos_angle = ray->cos_angle;
	data->miniray[u].sin_angle = ray->sin_angle;
}

void	draw_miniray(t_data *data, int u)
{
	t_coord		p1;
	t_coord		p2;
	t_coord		delta;
	float		epsilon;
	t_miniray	mini;

	mini = data->miniray[u];
	p1.x = PLAYER_X;
	p1.y = PLAYER_Y;
	p2.x = p1.x + mini.cos_angle * mini.distance * TILE_SIZE;
	p2.y = p1.y - mini.sin_angle * mini.distance * TILE_SIZE;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	epsilon = 1e-2f;
	if (fabsf(delta.x) < epsilon)
		draw_vertical(data, &p1, &p2);
	else if (fabsf(delta.y) < epsilon)
		draw_horizontal(data, &p1, &p2);
	else 
		draw_line(data, &p1, &delta);
}

static void	draw_vertical(t_data *data, t_coord *p1, t_coord *p2)
{
	int	x;
	int	y;
	int	y1;
	int	y2;

	x = round(p1->x);
	y1 = round(fmin(p1->y, p2->y));
	y2 = round(fmax(p1->y, p2->y));
	y = y1;
	while (y <= y2)
	{
		put_pixel_minimap(data, x, y, RAY_COL);
		y++;
	}
}

static void	draw_horizontal(t_data *data, t_coord *p1, t_coord *p2)
{
	int	x;
	int	y;
	int	x1;
	int	x2;

	y = round(p1->y);
	x1 = round(fmin(p1->x, p2->x));
	x2 = round(fmax(p1->x, p2->x));
	x = x1;
	while (x <= x2)
	{
		put_pixel_minimap(data, x, y, RAY_COL);
		x++;
	}
}

static void	draw_line(t_data *data, t_coord *p1, t_coord *delta)
{
	int		i;
	int		x1;
	int		y1;
	float	step;

	step = fmaxf(fabsf(delta->x), fabsf(delta->y));
	delta->x /= step;
	delta->y /= step;
	i = 0;
	while (i <= step)
	{
		if (delta->x < 0)
			x1 = floor(p1->x);
		else
			x1 = ceil(p1->x);
		if (delta->y < 0)
			y1 = floor(p1->y);
		else
			y1 = ceil(p1->y);
		put_pixel_minimap(data, x1, y1, RAY_COL);
		p1->x += delta->x;
		p1->y += delta->y;
		i++;
	}
}
