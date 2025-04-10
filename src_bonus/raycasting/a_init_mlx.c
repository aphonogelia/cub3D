/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_init_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:53:51 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/10 07:52:24 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void			init_mlx(t_data *data);
void			init_player(t_data *data);
static float	calc_angle(char c);

void	init_mlx(t_data *data)
{
	init_player(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	mlx_get_monitor_size(0, &data->mlx->width, &data->mlx->height);
	mlx_set_window_size(data->mlx, data->mlx->width, data->mlx->height);
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	data->miniray = NULL;
}

void	init_player(t_data *data)
{
	data->player.x = data->input.play_x + 0.5;
	data->player.y = data->input.play_y + 0.5;
	data->player.x_offset = PLAYER_X - data->player.x * TILE_SIZE;
	data->player.y_offset = PLAYER_Y - data->player.y * TILE_SIZE;
	data->player.angle_r = deg_to_rad(calc_angle(data->input.player_dir));
}

static float	calc_angle(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'W')
		return (180);
	else if (c == 'S')
		return (270);
	else
		return (0);
}
