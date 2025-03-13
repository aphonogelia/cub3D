/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_init_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:53:51 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/11 16:35:32 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void			init_mlx(t_data *data);
static void		init_player(t_data *data);
static float	calculate_angle(char c);

/* need to rework on image size - resizing when th ewindow is resized 
void resize_callback(int32_t width, int32_t height, void* param)
{
    // Handle the resize event here
    // width and height are the new dimensions of the window
}
// In your main function or initialization code
mlx_resize_hook(mlx, resize_callback, additional_param);
*/

void	init_mlx(t_data *data)
{
	init_player(data);
	init_doors(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	// mlx_get_monitor_size(0, &data->mlx->width, &data->mlx->height);
	// mlx_set_window_size(data->mlx, data->mlx->width, data->mlx->height);
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
}

static void	init_player(t_data *data)
{
	data->player.x = data->input.play_x * TILE_SIZE + OFFSET;
	data->player.y = data->input.play_y * TILE_SIZE + OFFSET;
	data->player.angle_r = degree_to_rad(calculate_angle(data->input.cardinal));
}

static float	calculate_angle(char c)
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
