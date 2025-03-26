/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 04:33:38 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/26 18:03:06 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

static void		save_door(t_data *data, int row, int col, int door_nbr);
static int		is_exit_door(t_data *data, int row, int col);

void	init_doors(t_data *data)
{
	int	j;
	int	doors_nbr;
	int	i;

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
					handle_error("Doors number exceed maximum\n", data);
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
	data->doors[door_nbr].x = col;
	data->doors[door_nbr].y = row;
	data->doors[door_nbr].open = 0;
	data->doors[door_nbr].exit_game = is_exit_door(data, row, col);
}

static int	is_exit_door(t_data *data, int row, int col)
{
	if (row == 0)
		return (1);
	if (data->input.map[row - 1][col] == ' ')
		return (1);
	if (row == data->input.h_map - 1)
		return (1);
	if (data->input.map[row + 1][col] == ' ')
		return (1);
	if (col == 0)
		return (1);
	if (data->input.map[row][col - 1] == ' ')
		return (1);
	if (data->input.map[row][col + 1] == ' ' || data->input.map[row][col
		+ 1] == '\0')
		return (1);
	return (0);
}
