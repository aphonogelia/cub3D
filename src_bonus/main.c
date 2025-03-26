/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:57:54 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/26 18:09:26 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

static void	first_screen(t_data *data);

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
	first_screen(data);
	mlx_image_to_window((data)->mlx, (data)->img, 0, 0);
	mlx_resize_hook(data->mlx, &resize_hook, data);
	// mlx_close_hook((&data)->mlx, &close_window, &data);
	mlx_loop_hook((data)->mlx, &hoop_func, data);
	// mlx_cursor_hook((data)->mlx, &mouse_callback, data);
	mlx_key_hook((data)->mlx, &keys_handle, data);
	mlx_loop((data)->mlx);
	mlx_terminate((data)->mlx);
	clean_textures(data);
	clean_parse(data);
	free(data);
	return (0);
}

static void	first_screen(t_data *data)
{
	init_mlx(data);
	welcome_screen(data, WELCOME_SCREEN);
	load_textures(data);
	draw_ceiling_floor(data);
	draw_walls(data);
	draw_minimap(data);
	print_data(data);
}
