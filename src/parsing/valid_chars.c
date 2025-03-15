/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbar <inbar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:20:57 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/15 14:38:53 by inbar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void		handle_player(t_data *data, int i, int j);
static int		is_player(char c);
static int		is_valid_char(char c);

//extracts player position and direction, returns error if found invalid char
//bc of extracting player's position, should happen after trimming map lines
int	valid_chars(t_data *data, int i, int j)
{
	char	c;

	i = -1;
	while (data->input.map[++i] != NULL)
	{
		j = -1;
		while (data->input.map[i][++j] != '\0')
		{
			c = data->input.map[i][j];
			if (is_player(c))
			{
				if (data->input.play_x != -1)
					return (err_msg("Multiple players in map :/", PARSE_ERR));
                handle_player(data, i, j);
				continue ;
			}
			if (!is_valid_char(c))
				return (err_msg("Forbbiden character in map:/", PARSE_ERR));
		}
	}
	if (data->input.play_x != -1)
		return (SUCCESS);
	return (err_msg("No player found in map :/", PARSE_ERR));
}

static int	is_valid_char(char c)
{
	if (c == ' ' || c == '1' || c == '0')
		return (1);
	return (0);
}

//extract player's info and change it to '0'
static void	handle_player(t_data *data, int i, int j)
{
	data->input.play_x = j;
	data->input.play_y = i;
	data->input.player_dir = data->input.map[i][j];
	data->input.map[i][j] = '0';
}

//returns 1 if char is a player char
static int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}