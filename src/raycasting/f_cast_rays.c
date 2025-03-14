/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cast_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:58 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/14 15:59:52 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void			cast_rays(t_data *data, t_ray *ray);
static void		direction(t_ray *ray);
static void		calcul_dist_per_unit(t_ray *ray);
static void		init_position_dist(t_data *data, t_ray *ray);
static float	find_distance(t_data *data, t_ray *ray);
static bool		wall_check(t_data *data, t_ray *ray);

void	cast_rays(t_data *data, t_ray *ray)
{
	direction(ray);
	calcul_dist_per_unit(ray);
	init_position_dist(data, ray);
	ray->distance = find_distance(data, ray);
	ray->corrected_distance = ray->distance * TILE_SIZE * ray->cos_angle_diff;
}

// Direction x and y + Distance to the first tile 
static void	direction(t_ray *ray)
{
	if (ray->cos_angle > 0) 
		ray->step_x = 1;
	else 
		ray->step_x = -1;
	if (ray->sin_angle < 0) 
		ray->step_y = 1;
	else 
		ray->step_y = -1;
}

// Calculate hypotenuse lengths, avoiding division by zero
// LENGTH OF THE RAY FOR ONE GRID CELL - x + 1 = ray + hypo_x
static void	calcul_dist_per_unit(t_ray *ray)
{
	if (ray->cos_angle == 0)
		ray->hypo_x = MAX_DIST;
	else
		ray->hypo_x = fabsf(1 / ray->cos_angle);
	if (ray->sin_angle == 0)
		ray->hypo_y = MAX_DIST;
	else
		ray->hypo_y = fabsf(1 / ray->sin_angle);
}

// INIT POSITION - in int for the DDA + FIRST DISTANCE 
static void	init_position_dist(t_data *data, t_ray *ray)
{
	float	x;
	float	y;

	ray->map_x = (int)((data->player.x - OFFSET) / TILE_SIZE);
	ray->map_y = (int)((data->player.y - OFFSET) / TILE_SIZE);
	x = ((data->player.x - OFFSET) / TILE_SIZE);
	y = ((data->player.y - OFFSET) / TILE_SIZE);
	if (ray->step_x > 0) 
		ray->dist_x = (ray->map_x + 1 - x) * ray->hypo_x;
	else 
		ray->dist_x = (x - ray->map_x) * ray->hypo_x;
	if (ray->step_y > 0) 
		ray->dist_y = (ray->map_y + 1 - y) * ray->hypo_y;
	else 
		ray->dist_y = (y - ray->map_y) * ray->hypo_y;
}

static float	find_distance(t_data *data, t_ray *ray)
{
	while (42) 
	{
		if (ray->dist_x < ray->dist_y)
			ray->map_x += ray->step_x;
		else 
			ray->map_y += ray->step_y;
		if (wall_check(data, ray) == true)
		{
			if (ray->dist_x < ray->dist_y)
				return (-ray->dist_x);
			else 
				return (ray->dist_y);
		}
		if (ray->dist_x < ray->dist_y)
			ray->dist_x += ray->hypo_x;
		else 
			ray->dist_y += ray->hypo_y;
	}
}

static bool	wall_check(t_data *data, t_ray *ray)
{
	if (data->input.map[ray->map_y][ray->map_x] == '1')
		return (true);
	return (false);
}
