/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:57:54 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/01 19:07:24 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

static void	clean_up(t_data *data);

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
	if (status == SUCCESS)
	{
		init_mlx(data);
		welcome_screen(data, WELCOME_SCREEN);
		load_textures(data);
		mlx_image_to_window((data)->mlx, (data)->img, 0, 0);
		mlx_resize_hook(data->mlx, &resize_hook, data);
		mlx_loop_hook((data)->mlx, &hoop_func, data);
		mlx_key_hook((data)->mlx, &keys_handle, data);
		mlx_loop((data)->mlx);
		clean_up(data);
		mlx_terminate(data->mlx);
	}
	free(data);
	return (status);
}

static void	clean_up(t_data *data)
{
	if (data->screen.is_welcome)
		clean_menus(data);
	clean_parse(data);
	clean_textures(data);
}
