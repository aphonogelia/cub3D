/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:43:52 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/22 17:18:10 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void		draw_minimap(t_data *data);
static void	draw_miniwalls(t_data *data);
static void	draw_player(t_data *data);
static void	draw_tiles(mlx_image_t *img, t_coord coord, int size, uint32_t col);

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
	t_coord		coord;
	uint32_t	i;
	uint32_t	j;

	coord.x = data->player.x * TILE_SIZE + OFFSET;
	coord.y = data->player.y * TILE_SIZE + OFFSET;
	i = coord.y - TILE_SIZE / 8;
	while (i < coord.y + TILE_SIZE / 8)
	{
		j = coord.x - TILE_SIZE / 8;
		while (j < coord.x + TILE_SIZE / 8)
		{
			if (j < data->img->height && i < data->img->width)
				mlx_put_pixel(data->img, j, i, PLY_COL);
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
			coord.x = x * TILE_SIZE + OFFSET;
			coord.y = y * TILE_SIZE + OFFSET;
			if (data->input.map[y][x] == '1')
				draw_tiles(data->img, coord, TILE_SIZE, TILE_COL);
			else if (data->input.map[y][x] == '2')
				draw_tiles(data->img, coord, TILE_SIZE, DOOR_COL);
			// else if (data->input.map[y][x] == '0' )
			// 	draw_tiles(data->img, coord, TILE_SIZE, FLOOR_COL);
			x++;
		}
		y++;
	}
}

static void	draw_tiles(mlx_image_t *img, t_coord coord, int size, uint32_t col)
{
	uint32_t	i;
	uint32_t	j;

	i = coord.y;
	while (i < coord.y + size)
	{
		j = coord.x;
		while (j < coord.x + size)
		{
			if (j < img->height && i < img->width)
				mlx_put_pixel(img, j, i, col);
			j++;
		}
		i++;
	}
}
