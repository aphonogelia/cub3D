/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_update_fov.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:36:24 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/26 11:56:48 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void		update_fov(t_data *data);
static void	update_angle(t_data *data);
static void	update_player(t_data *data);
static void	calculate_deltas(t_data *data, t_coord *delta);
static void	normalization(float *x, float *y);

void	update_fov(t_data *data)
{
	update_angle(data);
	update_player(data);
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

// static void collision(t_data *data, t_coord	*updated)
// {
//     // ... (existing code for calculating updated position) ...

//     bool can_move_x = !close_wall(data, updated->x, data->player.y);
//     bool can_move_y = !close_wall(data, data->player.x, updated->y);

//     // Check if the player is in a door zone
//     t_door *current_door = get_door_at(data, (int)data->player.x, (int)data->player.y);
//     if (current_door && door_zone(data, current_door, data->player.x, data->player.y))
//     {
//         // Allow movement parallel to the door
//         if (current_door->x == (int)data->player.x)
//         {
//             // Door is vertical, allow Y movement
//             data->player.y = updated->y;
//         }
//         else
//         {
//             // Door is horizontal, allow X movement
//             data->player.x = updated->x;
//         }
//     }
//     else
//     {
//         // Normal movement logic
//         if (can_move_x) data->player.x = updated->x;
//         if (can_move_y) data->player.y = updated->y;
//     }

//     if (can_move_x || can_move_y)
//         data->flag_refresh = true;
// }

// we calculate the new position. CTRL: speed * 2. We update the positions only
// if it is not encountering a wall.
static void	update_player(t_data *data)
{
	t_coord	updated;
	t_coord	delta;
	float	speed;

	speed = MVT_SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT_CONTROL)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT_CONTROL))
		speed *= 2;
	updated.x = data->player.x;
	updated.y = data->player.y;
	calculate_deltas(data, &delta);
	updated.x += speed * delta.x;
	updated.y += speed * delta.y;
	if (close_wall(data, updated.x, data->player.y) == false)
		data->player.x = updated.x;
	if (close_wall(data, data->player.x, updated.y) == false)
		data->player.y = updated.y;
}

// we move according to our angle
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

// Without scaling, the player might move faster when pressing multiple keys
// simultaneously (e.g., moving diagonally with W and D), because the combined
// deltas will result in a larger magnitude than moving in a single direction.
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
