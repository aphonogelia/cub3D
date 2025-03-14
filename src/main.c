/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:57:54 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/14 20:46:03 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void resize_hook(int32_t width, int32_t height, void* param)
{
	t_data	*data;

	(void)width;
	(void)height;
	data = (t_data *)param;

	// if (data->screen.is_welcome)
	// {
    //     mlx_delete_image(data->mlx, data->screen.welcome_img);
        
    //     data->screen.welcome_img = mlx_new_image(data->mlx, width, height);
    //     if (!data->screen.welcome_img)
    //         exit_err(data, "Failed to create resized welcome screen", FAILURE);
        
	// 	draw_on_screen(data, height, width);
			
	// 	if (mlx_image_to_window(data->mlx, data->screen.welcome_img, 0, 0) < 0)
	// 		exit_err(data, "Failed to put resized welcome screen to window", FAILURE);
    // }
    // else
		data->flag_refresh = true;
}

// mlx_set_setting(MLX_STRETCH_IMAGE, true);
int	main(int ac, char **av)
{
	t_data	data;
	int		status;

	if (ac != 2)
		return (err_msg("Invalid argument number", PARSE_ERR));
	init_data((&data));
	status = parser(av[1], &data);
	if (status != SUCCESS)
		return (status);
	init_mlx(&data);
	
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	
	welcome_screen(&data);
	
	load_textures(&data);
	
	mlx_resize_hook(data.mlx, &resize_hook, &data);
	mlx_close_hook(data.mlx, &close_window, &data);
	mlx_loop_hook(data.mlx, &hoop_func, &data);
	mlx_key_hook(data.mlx, &escape_handle, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	clean_textures(&data);
	clean_parse(&data);
	return (0);
}
