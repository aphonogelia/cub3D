/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:44:10 by inbar             #+#    #+#             */
/*   Updated: 2025/03/14 18:48:43 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_space(t_data *data, int row, int col);
static int	check_zero(t_data *data, int row, int col);
static int	check_top_bottom(t_data *data);
static int	is_wall(t_data *data, int row, int col);


//returns SUCCESS if map is according to rules
int	valid_map(t_data *data, int status)
{
	int		i;
	int		col;
	char	c;

	status = check_top_bottom(data);
	i = -1;
	while (data->input.map[++i] != NULL && status == SUCCESS)
	{
		col = 0;
		while (data->input.map[i][col + 1] != '\0')
			col++;
		if (!is_wall(data, i, col) && data->input.map[i][col] != ' ')
			return (err_msg("Map contains open walls :/", PARSE_ERR));
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

//if col is not 0 -> leftside must be 1 or ' '
//if row isnt last row -> line down must be 1 or ' '
static int	check_space(t_data *data, int row, int col)
{
	char	**map;
	char	*msg;
	char	c;

	msg = "Map contains open walls :/";
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

	msg = "Map contains open walls :/";
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

//returns 1 if both top and bottom lines of the map contain only '1's or spaces
static int	check_top_bottom(t_data *data)
{
	int	j;
	int	bottom;

	j = -1;
	while (data->input.map[0][++j] != '\0')
	{
		if (!is_wall(data, 0, j) && data->input.map[0][j] != ' ')
			return (err_msg("Map contains open walls1 :/", PARSE_ERR));
	}
	j = -1;
	bottom = data->input.h_map - 1;
	while (data->input.map[bottom][++j] != '\0')
	{
		if (!is_wall(data, bottom, j)
			&& data->input.map[bottom][j] != ' ')
			return (err_msg("Map contains open walls :/", PARSE_ERR));
	}
	return (SUCCESS);
}

//returns 1 if value in map should be treated as a wall
static int	is_wall(t_data *data, int row, int col)
{
	if (data->input.map[row][col] == '1')
		return (1);
	return (0);
}