/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_utils_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:31:50 by ilazar            #+#    #+#             */
/*   Updated: 2025/04/04 14:04:00 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

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
	if (str[i] == '1' || str[i] == '2')
		return (&str[i]);
	return (NULL);
}

// returns 1 if value in map should be treated as a wall
int	is_wall(t_data *data, int row, int col)
{
	if (data->input.map[row][col] == '1' || data->input.map[row][col] == '2')
		return (1);
	return (0);
}
