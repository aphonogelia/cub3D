/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cast_rays_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:06:50 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/25 19:11:56 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

bool			wall_check(t_data *data, t_ray *ray);
static t_door	*get_door_at(t_data *data, t_ray *ray);
void			wall_orient(t_data *data, t_ray *ray);

bool	wall_check(t_data *data, t_ray *ray)
{
	t_door	*door;

	if (data->input.map[ray->map_y][ray->map_x] == WALL)
		return (true);
	else if (data->input.map[ray->map_y][ray->map_x] == DOOR)
	{
		door = get_door_at(data, ray);
		if (door && !door->open)
			return (true);
		return (true);
	}
	return (false);
}

// finds appropriate door according to map coords
static t_door	*get_door_at(t_data *data, t_ray *ray)
{
	int	map_x;
	int	map_y;
	int	doors_nbr;
	int	i;

	map_x = ray->map_x;
	map_y = ray->map_y;
	doors_nbr = data->input.doors_nbr;
	i = -1;
	while (++i < doors_nbr)
	{
		if ((int)data->doors[i].x == map_x && (int)data->doors[i].y == map_y)
			return (&data->doors[i]);
	}
	return (NULL);
}

// Wall orientation
void	wall_orient(t_data *data, t_ray *ray)
{
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
	ray->wall_x -= floorf(ray->wall_x);
}
