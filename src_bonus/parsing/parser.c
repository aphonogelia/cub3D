/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:11:28 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/10 18:44:51 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// map validation

#include "../../inc/cub3d.h"

static int	valid_map_file(char *name, int *fd);
static int	elements_finder(int fd, t_data *data, int status);
static int	save_map(int fd, t_data *data, char **line, int *found_map);
static char	**add_line_to_arr(char **map, char *line, int *length);

int	parser(char *file_name, t_data *data)
{
	int	fd;
	int	status;

	status = valid_map_file(file_name, &fd);
	if (status == SUCCESS)
		status = elements_finder(fd, data, 0);
	close(fd);
	if (status == SUCCESS)
		status = trim_lines(data);
	if (status == SUCCESS)
		status = valid_chars(data, 0, 0);
	if (status == SUCCESS)
		status = valid_map(data, status);
	if (status != SUCCESS)
		clean_parse(data);
	return (status);
}

// check for no spaces in file's name, for .cub format and if file exists
static int	valid_map_file(char *name, int *fd)
{
	int	i;

	if (name[0] == '\0')
		return (err_msg("Empty file name :/", PARSE_ERR));
	i = 0;
	while (name[i] != '\0' && name[i] != '.')
	{
		if (name[0] == ' ')
			return (err_msg("No spaces in the filename please :/", PARSE_ERR));
		i++;
	}
	if (ft_strcmp(&name[i], ".cub") != 0)
		return (err_msg("Wrong file format. Should be of format \".cub\" :/",
				PARSE_ERR));
	*fd = open(name, O_DIRECTORY);
	if (*fd != -1)
		return (err_msg("File is a directory :/", PARSE_ERR));
	*fd = open(name, O_RDONLY);
	if (*fd == -1)
		return (err_msg("File has no permissions or doesn't exists :/",
				FAILURE));
	return (SUCCESS);
}

// finds the differenct map file elements
static int	elements_finder(int fd, t_data *data, int status)
{
	char	*line;
	int		found_map;

	line = NULL;
	found_map = 0;
	status = SUCCESS;
	while (status != PARSE_ERR)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		if (!line && found_map)
			return (status);
		if (!line)
			return (err_msg("No map found in file :/", PARSE_ERR));
		if (line_empty(line))
			continue ;
		if (valid_first_occurance(line) != NULL)
			status = save_map(fd, data, &line, &found_map);
		else
			status = parse_elements(line, data, found_map);
	}
	free(line);
	return (status);
}

// save the map to an array
// make sure that there isn't invalid text under the map
static int	save_map(int fd, t_data *data, char **line, int *found_map)
{
	int		length;
	char	**map;

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
		if (!valid_first_occurance(*line))
		{
			if (!line_empty(*line))
				return (err_msg("Invalid map :/", PARSE_ERR));
			break ;
		}
		map = add_line_to_arr(map, *line, &length);
	}
	data->input.map = map;
	*found_map = 1;
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
