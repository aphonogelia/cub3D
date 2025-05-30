/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:18:37 by ilazar            #+#    #+#             */
/*   Updated: 2025/04/10 07:56:55 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

static int	valid_map_file(char *name, int *fd);
static int	elements_finder(int fd, t_data *data, int status);

int	parser(char *file_name, t_data *data)
{
	int	fd;
	int	status;

	status = valid_map_file(file_name, &fd);
	if (status == SUCCESS)
		status = elements_finder(fd, data, 0);
	if (status == SUCCESS)
	{
		close(fd);
		status = trim_lines(data);
	}
	if (status == SUCCESS)
		status = valid_chars(data, 0, 0);
	if (status == SUCCESS)
		status = valid_map(data, status, -1);
	if (status == SUCCESS)
		status = parse_doors(data);
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
		if (name[i] == ' ')
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
		return (err_msg("File has no permissions or doesn't exist :/",
				PARSE_ERR));
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
	get_next_line(-1);
	return (status);
}

void	clean_parse(t_data *data)
{
	if (data->input.map)
		free_2d_char(data->input.map);
	if (data->input.no)
		free(data->input.no);
	if (data->input.so)
		free(data->input.so);
	if (data->input.we)
		free(data->input.we);
	if (data->input.ea)
		free(data->input.ea);
}
