/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:14:07 by ilazar            #+#    #+#             */
/*   Updated: 2025/04/01 19:21:22 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

void			doors_interaction(t_player *player, t_door *doors,
					int doors_nbr, t_data *data);
static float	distance_to_door(t_player *player, t_door door);
static void		close_all_doors(t_door *doors, int doors_nbr);
static void		exit_game(t_data *data, int doors_nbr);

void	doors_interaction(t_player *player, t_door *doors, int doors_nbr,
		t_data *data)
{
	int		i;
	float	dis_to_door;

	i = -1;
	while (++i <= doors_nbr)
	{
		dis_to_door = distance_to_door(player, doors[i]);
		if (doors[i].open && (dis_to_door < 2.5f && dis_to_door > 1.0f))
		{
			doors[i].open = !doors[i].open;
			data->flag_refresh = true;
			break ;
		}
		else if (!doors[i].open && dis_to_door < 2.5f)
		{
			if (doors[i].exit_game == 1)
				exit_game(data, doors_nbr);
			else
				doors[i].open = !doors[i].open;
			break ;
		}
	}
}

static float	distance_to_door(t_player *player, t_door door)
{
	float	x;
	float	y;

	x = door.x + (0.5);
	y = door.y + 0.5;
	return (sqrtf((player->x - x) * (player->x - x) + (player->y - y)
			* (player->y - y)));
}

static void	close_all_doors(t_door *doors, int doors_nbr)
{
	int	i;

	i = -1;
	while (++i <= doors_nbr)
		doors[i].open = 0;
}

static void	exit_game(t_data *data, int doors_nbr)
{
	welcome_screen(data, END_SCREEN);
	init_player(data);
	close_all_doors(data->doors, doors_nbr);
}
