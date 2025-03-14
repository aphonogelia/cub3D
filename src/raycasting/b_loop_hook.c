/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_loop_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:43:01 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/14 15:59:08 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	hoop_func(void *param);
void	clear_image(t_data *data);

void	hoop_func(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	update_angle(data);
	update_player(data);
	if (data->flag_refresh == true)
	{
		draw_ceiling_floor(data);
		draw_walls(data);
		data->flag_refresh = false;
	}
}
