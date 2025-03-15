/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbar <inbar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:57:54 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/15 15:09:41 by inbar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void resize_hook(int32_t width, int32_t height, void* param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->screen.is_welcome)
    {
        mlx_resize_image(data->screen.background, width, height);
        data->screen.welcome_img->instances[0].x = \
		(width - data->screen.welcome_img->width) / 2;
        data->screen.welcome_img->instances[0].y = \
		 (height - data->screen.welcome_img->height) / 2;
    }
	else
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
