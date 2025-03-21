/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_init_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:53:51 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/21 15:48:09 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void			init_mlx(t_data *data);
static void		init_player(t_data *data);
static float	calc_angle(char c);

void	init_mlx(t_data *data)
{
	init_player(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	mlx_get_monitor_size(0, &data->mlx->width, &data->mlx->height);
	mlx_set_window_size(data->mlx, data->mlx->width, data->mlx->height);
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
}

static void	init_player(t_data *data)
{
	data->player.x = data->input.play_x + 0.5;
	data->player.y = data->input.play_y + 0.5;
	data->player.angle_r = deg_to_rad(calc_angle(data->input.player_dir));
	printf("init pos x, y = %.2f, %.2f\n", data->player.x, data->player.y);
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
