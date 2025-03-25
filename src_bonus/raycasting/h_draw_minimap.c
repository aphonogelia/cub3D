/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:43:52 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/25 13:21:26 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void		draw_minimap(t_data *data);
static void	draw_miniwalls(t_data *data);
static void	draw_player(t_data *data);
static void	draw_tiles(t_data *data, t_coord coord);

void	draw_minimap(t_data *data)
{
	int	i;

	draw_miniwalls(data);
	draw_player(data);
	i = 0;
	while (i < data->mlx->width)
	{
		draw_miniray(data, i);
		i++;
	}
	free(data->miniray);
	data->miniray = NULL; 
}

static void	draw_player(t_data *data)
{
	uint32_t	i;
	uint32_t	j;

	i = PLAYER_Y - TILE_SIZE / 2;
	while (i < PLAYER_Y + TILE_SIZE / 2)
	{
		j = PLAYER_X - TILE_SIZE / 2;
		while (j < PLAYER_X + TILE_SIZE / 2)
		{
			if (j < data->img->height && i < data->img->width)
				mlx_put_pixel(data->img, j, i, PLAYER_COL);
			j++;
		}
		i++;
	}
}

static void	draw_miniwalls(t_data *data)
{
	int		x;
	int		y;
	t_coord	coord;

	x = 0;
	y = 0;
	while (y < data->input.h_map)
	{
		x = 0;
		while (x < data->input.w_map)
		{
			coord.x = (x - data->player.x) * TILE_SIZE + PLAYER_X;
			coord.y = (y - data->player.y) * TILE_SIZE + PLAYER_Y;
			if (data->input.map[y][x] == '1')
				draw_tiles(data, coord);
			x++;
		}
		y++;
	}
}

static void	draw_tiles(t_data *data, t_coord coord)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			put_pixel_minimap(data, coord.x + j, coord.y + i, TILE_COL);
			j++;
		}
		i++;
	}
}
