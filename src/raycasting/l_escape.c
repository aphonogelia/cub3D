/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_escape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbar <inbar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:10:25 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/15 14:55:46 by inbar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Consider adding collision detection in translation_press to prevent moving 
through walls. The update_play distance (50 units) seems large. Consider using a 
smaller value for smoother update_play. In orientation_press, you might want to 
normalize the angle to keep it between 0 and 2π. Consider adding a constant for 
the rotation angle (5 degrees) for easier adjustment. In update_display, you 
might want to add error checking for mlx functions.*/

/* 	- left and right arrow: look left and right in the maze.
	- W, A, S, and D: move the point of view through the maze.				  
	
// Key function callback data. for handling user input, allowing you to detect 
// key presses - Data related to the mlx_key_hook function
typedef struct mlx_key_data
{
	keys_t			key; 		// The key that was pressed.
	action_t		action; 	// The action that was done with the key.
	int32_t			os_key; 	// The os_key is unique for every key. 
	modifier_key_t	modifier; 	// modifier key that was pressed, 0 if no key 
								was pressed.
}		mlx_key_data_t;	

The keydata struct is automatically passed when calling 
// typedef void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param);
	*/

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
        return;
    }
	if (keys.key == MLX_KEY_ESCAPE && keys.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
