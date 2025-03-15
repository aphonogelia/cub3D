/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_escape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:10:25 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/15 15:49:36 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Handle welcome screen dismissal and handles ESC
void	escape_handle(mlx_key_data_t keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->screen.is_welcome && keys.action == MLX_PRESS)
	{
		if (keys.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);
        mlx_delete_image(data->mlx, data->screen.welcome_img);
		mlx_delete_image(data->mlx, data->screen.background);
		// mlx_delete_texture(data->screen.texture);
		data->screen.is_welcome = false;
		return ;
	}
	if (keys.key == MLX_KEY_ESCAPE && keys.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
