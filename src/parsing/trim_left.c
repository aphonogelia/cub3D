/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:01:22 by inbar             #+#    #+#             */
/*   Updated: 2025/03/14 19:20:10 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_min_start(t_data *data, int *min_start, int i);

int	trim_lines(t_data *data)
{
	int		status;

	status = trim_leftend(data);
	if (status == SUCCESS)
		status = trim_rightend(data);
	return (status);
}

//trims all spaces from the left and right sides of the map, trims \n
//saves map height
//may return malloc err or parse err
int	trim_leftend(t_data *data)
{
	int		min_start;
	int		len;
	int		i;
	char	*tmp;

	min_start = 0;
	if (get_min_start(data, &min_start, 0) == PARSE_ERR)
		return (PARSE_ERR);
	i = -1;
	while (data->input.map[++i] != NULL)
	{
		len = ft_strlen(data->input.map[i]);
		if (data->input.map[i][len - 1] == 10)
			len--;
		tmp = ft_substr(data->input.map[i], min_start, len - min_start);
		if (tmp == NULL)
			return (MALLOC_ERR);
		free(data->input.map[i]);
		data->input.map[i] = ft_strdup(tmp);
		if (data->input.map[i] == NULL)
		return (MALLOC_ERR);
		free(tmp);
	}
	data->input.h_map = i;
	return (SUCCESS);
}

//find the leftmost start of the lines in the map array
static int	get_min_start(t_data *data, int *min_start, int i)
{
	int		start;
	char	*line_start;

	line_start = valid_first_occurance(data->input.map[0]);
	if (line_start == NULL)
		return (PARSE_ERR);
	*min_start = line_start - data->input.map[0];
	i = 0;
	while (data->input.map[++i] != NULL)
	{
		line_start = valid_first_occurance(data->input.map[i]);
		if (line_start == NULL)
			return (PARSE_ERR);
		start = line_start - data->input.map[i];
		if (start < *min_start)
				*min_start = start;
	}
	return (SUCCESS);
}
