/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cast_rays_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:06:50 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/25 07:21:23 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

bool			wall_check(t_data *data, t_ray *ray);
t_door			*get_door_at(t_data *data, int map_x, int map_y);
void			wall_orient(t_data *data, t_ray *ray);

bool	wall_check(t_data *data, t_ray *ray)
{
	t_door	*door;

	if (data->input.map[ray->map_y][ray->map_x] == WALL)
		return (true);
	else if (data->input.map[ray->map_y][ray->map_x] == DOOR)
	{
		door = get_door_at(data, ray->map_x, ray->map_y);
		if (door)
		{
			ray->wall_orient = DOOR_TEXTURE;
			if (door->exit_game || !door->open)
				return (true);
		}
		ray->wall_orient = NO_ORIENT;
	}
	return (false);
}

// finds appropriate door according to map coords
t_door	*get_door_at(t_data *data, int map_x, int map_y)
{
	int	doors_nbr;
	int	i;

	// map_x = ray->map_x;
	// map_y = ray->map_y;
	doors_nbr = data->input.doors_nbr;
	i = -1;
	// printf("mapx: %d mapy: %d\n", map_x, map_y);
	while (++i <= doors_nbr)
	{
		if ((int)data->doors[i].x == map_x && (int)data->doors[i].y == map_y)
			return (&data->doors[i]);
	}
	return (NULL);
}

void wall_orient(t_data *data, t_ray *ray)
{
    // t_door *door = get_door_at(data, ray);
    
	int door = 0;
	if (ray->wall_orient == DOOR_TEXTURE)
		door = 1;
	
	if (ray->corr_dist < 0)
	{
		ray->distance *= -1;
		ray->corr_dist *= -1;
		if (ray->step_x > 0)
			ray->wall_orient = EAST;
		else 
			ray->wall_orient = WEST;
		ray->wall_x = data->player.y - ray->distance * ray->sin_angle ;
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_orient = SOUTH;
		else 
			ray->wall_orient = NORTH;
		ray->wall_x = data->player.x + ray->distance * ray->cos_angle;
	}
	// if (door != NULL)
	// if (ray->wall_orient == 7)
	if (door == 1)
		ray->wall_orient = DOOR_TEXTURE;
	ray->wall_x -= floorf(ray->wall_x);
}
// */