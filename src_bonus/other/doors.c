/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:14:07 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/25 07:26:31 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void 	doors_interaction(t_data *data);
static void	doors_hook(t_player *player, t_door *doors, int doors_nbr, t_data *data);
static float	distance_to_door(t_player *player, t_door *doors, int i);


void 	doors_interaction(t_data *data)
{
	// if (mlx_is_key_down(data->mlx, MLX_KEY_E))
	{
		doors_hook(&data->player, data->doors, data->input.doors_nbr, data);
		data->flag_refresh = true;
	}
}

void	exit_door(t_data *data)
{
	mlx_close_window(data->mlx);
}


static void	doors_hook(t_player *player, t_door *doors, int doors_nbr, t_data *data)
{
	int		i;
	float	door_vec_x;
	float	door_vec_y;
	float	distance;
	float	facing_door;

	i = -1;
	while (++i <= doors_nbr)
	{
		printf("Player position: (%f, %f)\n", player->x, player->y);
		printf("Door %d position: (%f, %f)\n", i, doors[i].x, doors[i].y);
		// printf("Distance to door %d: %f\n", i, distance_to_door(player,
		// doors, i));
		if (distance_to_door(player, doors, i) < DOOR_MAX_RANGE &&
		distance_to_door(player, doors, i) > DOOR_MIN_RANGE)
		{
			door_vec_x = doors[i].x - player->x;
			door_vec_y = doors[i].y - player->y;
			distance = sqrtf(door_vec_x * door_vec_x + door_vec_y * door_vec_y);
			if (distance == 0)
				distance = 1;
			door_vec_x = door_vec_x / distance;
			door_vec_y = door_vec_y / distance;
			facing_door = (cosf(player->angle_r) * door_vec_x)
				- (sinf(player->angle_r) * door_vec_y);
			printf("facing door (%f)\n", facing_door);
			if (facing_door > DOOR_FACING) // theshold for facing door
			{
				printf("door open\n");
				doors[i].open = !doors[i].open;
				data->flag_refresh = true;
				if (doors[i].exit_game == 1)
					exit_door(data);
					// printf("exit game\n");
				break ;
			}
		}
	}
}

static float	distance_to_door(t_player *player, t_door *doors, int i)
{
	return (sqrtf((player->x - doors[i].x) * (player->x - doors[i].x)
			+ (player->y - doors[i].y) * (player->y - doors[i].y)));
}


//player is locked inside door
//refresh flag
//end screen