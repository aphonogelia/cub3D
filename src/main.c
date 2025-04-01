/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:57:54 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/01 18:46:12 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	mlx_loop_hook(data.mlx, &hoop_func, &data);
	mlx_key_hook(data.mlx, &escape_handle, &data);
	mlx_loop(data.mlx);
	clean_menus(&data);
	clean_parse(&data);
	clean_textures(&data);
	mlx_terminate(data.mlx);
	return (0);
}
