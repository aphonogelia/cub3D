/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_escape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:10:25 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/29 16:31:02 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Handle welcome screen dismissal and handles ESC
void	escape_handle(mlx_key_data_t keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->screen.is_welcome)
	{
		if (keys.action == MLX_PRESS)
		{
			clean_menus(data);
			if (keys.key == MLX_KEY_ESCAPE && keys.action == MLX_PRESS)
				mlx_close_window(data->mlx);
			data->screen.is_welcome = false;
			data->flag_refresh = true;
		}
		return ;
	}
	if (keys.key == MLX_KEY_ESCAPE && keys.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keys.key == MLX_KEY_ESCAPE && keys.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
