/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_update_fov_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:36:24 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/01 19:06:35 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

bool		close_wall(t_data *data, float x, float y);
static bool	tile(t_data *data, float x, float y);

bool	close_wall(t_data *data, float x, float y)
{
	int		i;
	int		j;
	float	check_x;
	float	check_y;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			check_x = (x + i * PLAYER_SPACE);
			check_y = (y + j * PLAYER_SPACE);
			if (tile(data, check_x, check_y))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static bool	tile(t_data *data, float x, float y)
{
	int		map_x;
	int		map_y;
	t_door	*door;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x > data->input.w_map || map_y > data->input.h_map || map_x < 0
		|| map_y < 0)
		return (true);
	if (data->input.map[map_y][map_x] == WALL)
		return (true);
	if (data->input.map[map_y][map_x] == DOOR)
	{
		door = get_door_at(data, map_x, map_y);
		if (door && !door->open)
			return (true);
	}
	return (false);
}
