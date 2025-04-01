/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_key_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:10:25 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/01 18:34:05 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

// Handle welcome screen dismissal and handles ESC
void	keys_handle(mlx_key_data_t keys, void *param)
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
	else if (keys.key == MLX_KEY_E && keys.action == MLX_PRESS)
	{
		doors_interaction(&data->player, data->doors, data->input.doors_nbr,
			data);
		data->flag_refresh = true;
	}
}
