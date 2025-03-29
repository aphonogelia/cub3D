/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_key_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:10:25 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/29 16:23:10 by ilazar           ###   ########.fr       */
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

/* Consider adding collision detection in translation_press to prevent moving
through walls. The update_play distance (50 units) seems large. Consider using a
smaller value for smoother update_play. In orientation_press,
	you might want to
normalize the angle to keep it between 0 and 2π. Consider adding a constant for
the rotation angle (5 degrees) for easier adjustment. In update_display, you
might want to add error checking for mlx functions.*/

/* 	- left and right arrow: look left and right in the maze.
	- W, A, S, and D: move the point of view through the maze.

// Key function callback data. for handling user input,
	allowing you to detect
// key presses - Data related to the mlx_key_hook function
typedef struct mlx_key_data
{
	keys_t			key; 		// The key that was pressed.
	action_t		action; 	// The action that was done with the key.
	int32_t			os_key; 	// The os_key is unique for every key.
	modifier_key_t	modifier; 	// modifier key that was pressed,
				0 if no key
								was pressed.
}		mlx_key_data_t;

The keydata struct is automatically passed when calling
// typedef void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param);
	*/