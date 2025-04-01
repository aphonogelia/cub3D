/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_loop_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:43:01 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/01 18:44:38 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void	hoop_func(void *param);

void	hoop_func(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->screen.is_welcome)
	{
		update_fov(data);
		if (data->flag_refresh == true)
		{
			draw_ceiling_floor(data);
			draw_walls(data);
			draw_minimap(data);
			data->flag_refresh = false;
		}
	}
}
