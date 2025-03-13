/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:06:11 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/11 17:54:17 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	degree_to_rad(int nb);

float	degree_to_rad(int nb)
{
	return (nb * (2 * M_PI) / 360.0);
}
/* 
float	rad_to_degree(float nb)
{
	return (nb / (2 * M_PI) * 360.0);
}
 */

// we check if not out of the map (theoritacally not possible as the player has
// to be surrounded by walls)
// we check if there is a tile ->  return TRUE
bool	tile(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)((x - OFFSET) / TILE_SIZE);
	map_y = (int)((y - OFFSET) / TILE_SIZE);
	if (map_x > data->input.w_map 
		|| map_y > data->input.h_map
		|| map_x < 0 || map_y < 0)
		return (true);
	if (data->input.map[map_y][map_x] == '1')
		return (true);
	return (false);
}