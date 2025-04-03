/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:11:28 by ilazar            #+#    #+#             */
/*   Updated: 2025/04/03 11:29:38 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	valid_map_file(char *name, int *fd);
static int	elements_finder(int fd, t_data *data, int status);
void		print_input(t_data *data);

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
	if (status != SUCCESS)
		clean_parse(data);
	if (status == SUCCESS)
		print_input(data);
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
	return (status);
}

void	print_input(t_data *data)
{
	int i;
	t_input input;

	input = data->input;
	printf("\n=== INPUT INFO ===\n");
	printf("Map Dimensions: %d x %d\n", input.w_map, input.h_map);
	printf("Textures:\n");
	printf("  North: %s\n", input.no);
	printf("  South: %s\n", input.so);
	printf("  West: %s\n", input.we);
	printf("  East: %s\n", input.ea);
	printf("Colors:\n");
	printf("  Floor: %#x\n", input.floor);
	printf("  Ceiling: %#x\n", input.sky);
	printf("Player:\n");
	printf("  (x, y): (%d, %d)\n", input.play_x, input.play_y);
	printf("  Facing: %c\n", input.player_dir);
	printf("\nMap:\n");
	i = 0;
	while (i < input.h_map)
	{
		printf("%s$\n", input.map[i]);
		i++;
	}
}