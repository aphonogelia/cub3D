/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_resize_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:32:23 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/14 16:32:40 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	(void)width;
	(void)height;
	data = (t_data *)param;
	data->flag_refresh = true;
}
