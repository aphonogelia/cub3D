/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:51:29 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/17 18:41:33 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

// adjust the player's angle based on mouse movement
void	mouse_callback(double xpos, double ypos, void *param)
{
	static double	last_x = -1;
	double			delta_x;
	t_data			*data;

	// static int      last_width = -1;
	data = (t_data *)param;
	// // mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	// // Check if the window size has changed
	// if (last_width != data->mlx->width) {
	//     last_width = data->mlx->width;
	//     last_x = -1;  // Reset last_x to force recalibration
	// }
	// // Initialize last_x if it's the first call or after window resize
	// if (last_x == -1) {
	//     last_x = xpos;
	//     return ;
	// }
	delta_x = xpos - last_x;
	if (xpos <= 0)
	{
		mlx_set_mouse_pos(data->mlx, data->mlx->width - 5, ypos);
		last_x = data->mlx->width - 5;
		return ;
	}
	if (xpos >= data->mlx->width - 1)
	{
		mlx_set_mouse_pos(data->mlx, 0, ypos);
		last_x = 0;
		return ;
	}
	data->player.angle_r -= (float)(delta_x * MOUSE_SENS);
	// Normalize the angle to keep it between 0 and 2*PI
	data->player.angle_r = fmodf(data->player.angle_r, 2 * M_PI);
	if (data->player.angle_r < 0)
		data->player.angle_r += 2 * M_PI;
	last_x = xpos;
}
