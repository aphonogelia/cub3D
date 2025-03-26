/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cast_rays_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:06:50 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/26 17:52:02 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

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

	doors_nbr = data->input.doors_nbr;
	i = -1;
	while (++i <= doors_nbr)
	{
		if ((int)data->doors[i].x == map_x && (int)data->doors[i].y == map_y)
			return (&data->doors[i]);
	}
	return (NULL);
}

void wall_orient(t_data *data, t_ray *ray)
{ 
	int orient;
	
	orient = NO_ORIENT;
	if (ray->corr_dist < 0)
	{
		ray->distance *= -1;
		ray->corr_dist *= -1;
		if (ray->step_x > 0)
			orient = EAST;
		else 
			orient = WEST;
		ray->wall_x = data->player.y - ray->distance * ray->sin_angle ;
	}
	else
	{
		if (ray->step_y > 0)
			orient = SOUTH;
		else 
			orient = NORTH;
		ray->wall_x = data->player.x + ray->distance * ray->cos_angle;
	}
	if (ray->wall_orient != DOOR_TEXTURE)
		ray->wall_orient = orient;
	ray->wall_x -= floorf(ray->wall_x);
}
