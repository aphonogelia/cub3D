/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:57:54 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/24 17:01:53 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

// mlx_set_setting(MLX_STRETCH_IMAGE, true);
int	main(int ac, char **av)
{
	t_data	*data;
	int		status;

	if (ac != 2)
		return (err_msg("Invalid argument number", PARSE_ERR));
	data = malloc(sizeof(t_data));
	if (!data)
		return (MALLOC_ERR);
	init_data((data));
	status = parser(av[1], data);
	if (status != SUCCESS)
		return (status);
	// print_input(&data.input);
	init_mlx(data);
	mlx_image_to_window((data)->mlx, (data)->img, 0, 0);
	welcome_screen(data);
	load_textures(data);
	mlx_resize_hook(data->mlx, &resize_hook, data);
	// clean_textures(&data);
	draw_ceiling_floor(data);
	draw_walls(data);
	draw_minimap(data);
	print_data(data);
	// mlx_close_hook((&data)->mlx, &close_window, &data);
	mlx_loop_hook((data)->mlx, &hoop_func, data);
	mlx_key_hook((data)->mlx, &escape_handle, data);
	mlx_cursor_hook((data)->mlx, &mouse_callback, data);
	mlx_loop((data)->mlx);
	mlx_terminate((data)->mlx);
	// printf("terminate error\n");
	clean_textures(data);
	clean_parse(data);
	free(data);
	return (0);
}
