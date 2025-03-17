/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:14:07 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/17 18:42:33 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static void		save_door(t_data *data, int row, int col, int door_nbr);
static int		is_exit_door(t_data *data, int row, int col);

void	init_doors(t_data *data)
{
	int	i;
	int	j;
	int	doors_nbr;

	i = 0;
	doors_nbr = -1;
	while (i < data->input.h_map)
	{
		j = 0;
		while (data->input.map[i][j] != '\0')
		{
			if (data->input.map[i][j] == '2')
			{
				doors_nbr++;
				if (doors_nbr > MAX_DOORS - 1)
					handle_error2("Doors exceed maximum :/", data, PARSE_ERR);
				save_door(data, i, j, doors_nbr);
			}
			j++;
		}
		i++;
	}
	data->input.doors_nbr = doors_nbr;
}

static void	save_door(t_data *data, int row, int col, int door_nbr)
{
	// printf("save door nbr %d\n", door_nbr);
	data->doors[door_nbr].x = col * TILE_SIZE + OFFSET + TILE_SIZE / 2;
	data->doors[door_nbr].y = row * TILE_SIZE + OFFSET + TILE_SIZE / 2;
	data->doors[door_nbr].open = 0;
	data->doors[door_nbr].exit_game = is_exit_door(data, row, col);
}

static int	is_exit_door(t_data *data, int row, int col)
{
	if (row == 0) // first row
		return (1);
	if (data->input.map[row - 1][col] == ' ')
		return (1);
	if (row == data->input.h_map - 1) // last row
		return (1);
	if (data->input.map[row + 1][col] == ' ') // row down
		return (1);
	if (col == 0) // first collum
		return (1);
	if (data->input.map[row][col - 1] == ' ') // left collum
		return (1);
	if (data->input.map[row][col + 1] == ' ' || data->input.map[row][col
		+ 1] == '\0')
		return (1);
	return (0);
}

static float	distance_to_door(t_player *player, t_door *doors, int i)
{
	return (sqrtf((player->x - doors[i].x) * (player->x - doors[i].x)
			+ (player->y - doors[i].y) * (player->y - doors[i].y)));
}

void	doors_interaction(t_player *player, t_door *doors, int doors_nbr)
{
	int		i;
	float	door_vec_x;
	float	door_vec_y;
	float	distance;
	float	facing_door;

	i = -1;
	while (++i <= doors_nbr)
	{
		// printf("Player position: (%f, %f)\n", player->x, player->y);
		// printf("Door %d position: (%f, %f)\n", i, doors[i].x, doors[i].y);
		// printf("Distance to door %d: %f\n", i, distance_to_door(player, doors, i));
		if (distance_to_door(player, doors, i) < INTERACTION_RANGE)
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
			// printf("facing door (%f)\n", facing_door);
			if (facing_door > 0.6f) // theshold for facing door
			{
				printf("door open\n");
				doors[i].open = !doors[i].open;
				if (doors[i].exit_game == 1)
					printf("exit game\n");
				break ;
			}
		}
	}
}
