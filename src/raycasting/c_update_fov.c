/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_update_fov.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:58:59 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/20 22:00:43 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		update_angle(t_data *data);
void		update_player(t_data *data);
static void	calculate_deltas(t_data *data, t_coord *delta);
static void	normalization(float *x, float *y);
static bool	close_wall(t_data *data, float x, float y);
static bool	tile(t_data *data, float x, float y);

// update the angle, stays between 0 and 2pi (fmod : float modulo)
void	update_angle(t_data *data)
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
void	update_player(t_data *data)
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

static bool	close_wall(t_data *data, float x, float y)
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
			printf("checking x, y = %.2f, %.2f\n", check_x, check_y);
			if (tile(data, check_x, check_y))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

// we check if there is a tile ->  return TRUE
static bool	tile(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x > data->input.w_map 
		|| map_y > data->input.h_map 
		|| map_x < 0 
		|| map_y < 0)
		return (true);
	if (data->input.map[map_y][map_x] == '1')
		return (true);
	return (false);
}
