/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_update_fov.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:58:59 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/11 17:18:29 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		update_fov(t_data	*data);
static void	update_angle(t_data *data);
static void	update_play_door(t_data *data);
static void	calculate_deltas(t_data *data, t_coord *delta);
static void	normalization(float *x, float *y);

void	update_fov(t_data	*data)
{
	update_angle(data);
	update_play_door(data);
}

// update the angle, stays between 0 and 2pi (fmod : float modulo)
static void	update_angle(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle_r += ROT_SPEED;
		data->flag_refresh = true;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle_r -= ROT_SPEED;
		data->flag_refresh = true;
	}
	data->player.angle_r = fmod(data->player.angle_r + 2 * M_PI, 2 * M_PI);
}

// we calculate the new position. CTRL: speed * 2. We update the positions only 
// if it is not encountering a wall. 
static void	update_play_door(t_data *data)
{
	t_coord	updated;
	t_coord	delta;
	float	speed;

	speed = MVT_SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT_CONTROL) || 
		mlx_is_key_down(data->mlx, MLX_KEY_LEFT_CONTROL))
		speed *= 2;
	updated.x = data->player.x;
	updated.y = data->player.y;
	calculate_deltas(data, &delta);
	updated.x += speed * delta.x;
	updated.y += speed * delta.y;
	if (tile(data, updated.x, data->player.y) == false)
		data->player.x = updated.x;
	if (tile(data, data->player.x, updated.y) == false)
		data->player.y = updated.y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
	{
		doors_interaction(&data->player, data->doors, data->input.doors_nbr);
		data->flag_refresh = true;
	}
}

// we move according to our angle
// Without scaling, the player might move faster when pressing multiple keys 
// simultaneously (e.g., moving diagonally with W and D), because the combined 
// deltas will result in a larger magnitude than moving in a single direction.
static void	calculate_deltas(t_data *data, t_coord *delta)
{
	t_mvt	mvt[4];
	float	cos_angle;
	float	sin_angle;
	int		i;

	cos_angle = cosf(data->player.angle_r);
	sin_angle = sinf(data->player.angle_r);
	mvt[0] = (t_mvt){MLX_KEY_W, +cos_angle, -sin_angle};
	mvt[1] = (t_mvt){MLX_KEY_S, -cos_angle, +sin_angle};
	mvt[2] = (t_mvt){MLX_KEY_A, -sin_angle, -cos_angle};
	mvt[3] = (t_mvt){MLX_KEY_D, +sin_angle, +cos_angle};
	delta->x = 0.0f;
	delta->y = 0.0f;
	i = 0;
	while (i < 4)
	{
		if (mlx_is_key_down(data->mlx, mvt[i].key)) 
		{
			delta->x += mvt[i].delta_x;
			delta->y += mvt[i].delta_y;
			data->flag_refresh = true;
		}
		i++;
	}
	normalization(&delta->x, &delta->y);
}

static void	normalization(float *x, float *y)
{
	float	scale;

	scale = sqrtf((*x) * (*x) + (*y) * (*y));
	if (scale > 1.0f)
	{
		*x /= scale;
		*y /= scale;
	}
}
