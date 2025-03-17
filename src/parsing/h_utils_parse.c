/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:31:50 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/17 18:06:12 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_2d_char(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int	ft_isspace(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

// returns 1 if line contains only spaces and tabs
int	line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (ft_isspace(line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

// returns 1 if first occurance of the string is a valid map char
// ignores tabs and spaces
char	*valid_first_occurance(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '1')
		return (&str[i]);
	return (NULL);
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
