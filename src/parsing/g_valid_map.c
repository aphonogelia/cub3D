/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_valid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:44:10 by inbar             #+#    #+#             */
/*   Updated: 2025/04/03 12:10:59 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_space(t_data *data, int row, int col);
static int	check_zero(t_data *data, int row, int col);
static int	check_top_bottom(t_data *data);
static int	is_wall(t_data *data, int row, int col);

int	check_end_line(t_data *data, int *col, int i)
{
	printf("check line:%s , i:%d\n", data->input.map[i], i);
	while (data->input.map[i][*col + 1] != '\0')
		*col = *col + 1;
	printf("c:%c$ col:%d\n", data->input.map[i][*col], *col);
	if (!is_wall(data, i, *col) && data->input.map[i][*col] != ' ')
	{
		// printf("%s, i:%d\n", data->input.map[i], i);
		printf("c:%c col:%d\n", data->input.map[i][*col], *col);
		return (err_msg("Map contains open walls1 :/", PARSE_ERR));
	}
	if (data->input.map[i][*col] != ' ' && data->input.map[i][*col + 1] != '\0')
	{
		*col = *col - 1;
		while (*col != 0)
		{
			if (data->input.map[i][*col] == '1')
				return (SUCCESS);
			*col = *col - 1;
		}
		return (err_msg("Map contains open walls11 :/", PARSE_ERR));
	}
	return (SUCCESS);
}

// returns SUCCESS if map is according to rules
int	valid_map(t_data *data, int status, int i)
{
	int		col;
	char	c;

	status = check_top_bottom(data);
	while (data->input.map[++i] != NULL && status == SUCCESS)
	{
		col = 0;
		status = check_end_line(data, &col, i);
		while (--col != 0 && status == SUCCESS)
		{
			c = data->input.map[i][col];
			if (is_wall(data, i, col))
				continue ;
			else if (c == ' ')
				status = check_space(data, i, col);
			else if (c == '0')
				status = check_zero(data, i, col);
		}
	}
	return (status);
}

// if col is not 0 -> leftside must be 1 or ' '
// if row isnt last row -> line down must be 1 or ' '
static int	check_space(t_data *data, int row, int col)
{
	char	**map;
	char	*msg;
	char	c;

	msg = "Map contains open walls2 :/";
	map = data->input.map;
	if (col != 0)
	{
		c = map[row][col - 1];
		if (!is_wall(data, row, col - 1) && c != ' ')
			return (err_msg(msg, PARSE_ERR));
	}
	if (row != (data->input.h_map - 1))
	{
		c = map[row + 1][col];
		if (!is_wall(data, row + 1, col) && c != ' ')
			return (err_msg(msg, PARSE_ERR));
	}
	return (SUCCESS);
}

// if col is not 0 -> leftside must be 1, 2 or 0 or player
// if row is not last one -> line down must be 1 or 0 or player
static int	check_zero(t_data *data, int row, int col)
{
	char	**map;
	char	*msg;
	char	c;

	msg = "Map contains open walls3 :/";
	map = data->input.map;
	if (col != 0)
	{
		c = map[row][col - 1];
		if (!is_wall(data, row, col - 1) && c != '0')
			return (err_msg(msg, PARSE_ERR));
	}
	if (row != data->input.h_map - 1)
	{
		c = map[row + 1][col];
		if (!is_wall(data, row + 1, col) && c != '0')
			return (err_msg(msg, PARSE_ERR));
	}
	return (SUCCESS);
}

// returns 1 if both top and bottom lines of the map contain only '1's or spaces
static int	check_top_bottom(t_data *data)
{
	int	j;
	int	bottom;

	j = -1;
	while (data->input.map[0][++j] != '\0')
	{
		if (!is_wall(data, 0, j) && data->input.map[0][j] != ' ')
			return (err_msg("Map contains open walls4 :/", PARSE_ERR));
	}
	j = -1;
	bottom = data->input.h_map - 1;
	while (data->input.map[bottom][++j] != '\0')
	{
		if (!is_wall(data, bottom, j) && data->input.map[bottom][j] != ' ')
			return (err_msg("Map contains open walls5 :/", PARSE_ERR));
	}
	return (SUCCESS);
}

// returns 1 if value in map should be treated as a wall
static int	is_wall(t_data *data, int row, int col)
{
	if (data->input.map[row][col] == '1')
		return (1);
	return (0);
}
