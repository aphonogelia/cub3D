/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:14:07 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/25 15:44:23 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void 	doors_interaction(t_data *data);
static void	doors_hook(t_player *player, t_door *doors, int doors_nbr, t_data *data);
static float	distance_to_door(t_player *player, t_door door);
// static float	angle_to_door(t_player *player, t_door door);


void 	doors_interaction(t_data *data)
{
	{
		// data->flag_refresh = true;
		doors_hook(&data->player, data->doors, data->input.doors_nbr, data);
		// data->flag_refresh = true;
	}
}

void	exit_door(t_data *data)
{
	mlx_close_window(data->mlx);
}


static void	doors_hook(t_player *player, t_door *doors, int doors_nbr, t_data *data)
{
	int		i;
	float 	dis_to_door;

	i = -1;
	while (++i <= doors_nbr)
	{
		printf("Player position: (%f, %f)\n", player->x, player->y);
		printf("Door %d position: (%f, %f)\n", i, doors[i].x, doors[i].y);
		printf("Distance to door %d: %f\n", i, distance_to_door(player, doors[i]));
		dis_to_door = distance_to_door(player, doors[i]);
		if (doors[i].open && (dis_to_door < 2.5f && dis_to_door > 1.0f))
		{	
			printf("door closed\n");
			doors[i].open = !doors[i].open;
			data->flag_refresh = true;
			break ;
		}
		else if (!doors[i].open && dis_to_door < 2.5f)
		{
			printf("door open\n");
			doors[i].open = !doors[i].open;
			// data->flag_refresh = true;
			if (doors[i].exit_game == 1)
				exit_door(data);
			break ;
		}
	}
}

static float	distance_to_door(t_player *player, t_door door)
{
	float x;
	float y;

	x = door.x + (0.5);
	y = door.y + 0.5;
	return (sqrtf((player->x - x) * (player->x - x)
			+ (player->y - y) * (player->y - y)));
}

//mouse
//refresh flag
//end screen