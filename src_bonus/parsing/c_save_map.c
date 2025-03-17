/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_save_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:44:44 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/17 18:38:47 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

int			save_map(int fd, t_data *data, char **line, int *found_map);
static int	invalid_line_start(char *line);
static char	**add_line_to_arr(char **map, char *line, int *length);

// save the map to an array
// make sure that there isn't invalid text under the map
int	save_map(int fd, t_data *data, char **line, int *found_map)
{
	int		length;
	char	**map;
	int		status;

	status = SUCCESS;
	if (*found_map)
		return (err_msg("Invalid map :/", PARSE_ERR));
	length = 1;
	map = (char **)malloc(sizeof(char *) * (2));
	map[0] = ft_strdup(*line);
	map[1] = NULL;
	while (*line != NULL)
	{
		free(*line);
		*line = get_next_line(fd);
		if (!*line)
			break ;
		status = invalid_line_start(*line);
		if (status != SUCCESS || (status == SUCCESS && line_empty(*line)))
			break ;
		map = add_line_to_arr(map, *line, &length);
	}
	data->input.map = map;
	*found_map = 1;
	return (status);
}

static int	invalid_line_start(char *line)
{
	if (!valid_first_occurance(line))
	{
		if (!line_empty(line))
			return (err_msg("Invalid map :/", PARSE_ERR));
	}
	return (SUCCESS);
}

// adds a new line to the map array
static char	**add_line_to_arr(char **map, char *line, int *length)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (*length + 2));
	i = 0;
	while (i < *length)
	{
		tmp[i] = ft_strdup(map[i]);
		free(map[i]);
		i++;
	}
	tmp[i] = ft_strdup(line);
	tmp[i + 1] = NULL;
	*length = *length + 1;
	free(map);
	return (tmp);
}
