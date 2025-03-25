/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_draw_miniray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:37:40 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/25 17:34:24 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

typedef struct s_line{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

void		draw_miniray(t_data *data, int u);
void		save_miniray(t_data *data, t_ray *ray, int u);
static void	draw_line(t_data *data, t_coord *p1, t_coord *p2);
static void	init(t_coord *p1, t_coord *p2, t_line *line);

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
	t_miniray	mini;

	mini = data->miniray[u];
	p1.x = PLAYER_X;
	p1.y = PLAYER_Y;
	p2.x = p1.x + mini.cos_angle * mini.distance * TILE_SIZE;
	p2.y = p1.y - mini.sin_angle * mini.distance * TILE_SIZE;
	draw_line(data, &p1, &p2);
}

static void	draw_line(t_data *data, t_coord *p1, t_coord *p2)
{
	t_line	line;
	int		e2;

	init(p1, p2, &line);
	while (42)
	{
		put_pixel_minimap(data, (int)p1->x, (int)p1->y, RAY_COL);
		if ((int)p1->x == (int)p2->x && (int)p1->y == (int)p2->y)
			break ;
		e2 = line.err;
		if (e2 > -line.dx)
		{
			line.err -= line.dy;
			p1->x += line.sx;
		}
		if (e2 < line.dy)
		{
			line.err += line.dx;
			p1->y += line.sy;
		}
	}
}

static void	init(t_coord *p1, t_coord *p2, t_line *line)
{
	line->dx = abs((int)p2->x - (int)p1->x);
	line->dy = abs((int)p2->y - (int)p1->y);
	if (p1->x < p2->x)
		line->sx = 1;
	else
		line->sx = -1;
	if (p1->y < p2->y)
		line->sy = 1;
	else
		line->sy = -1;
	if (line->dx > line->dy)
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}
