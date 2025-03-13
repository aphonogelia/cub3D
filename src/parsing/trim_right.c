/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:21:11 by ilazar            #+#    #+#             */
/*   Updated: 2025/02/19 12:50:58 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*shorten_line(t_data *data, int i, int len);
static char	*extend_line(t_data *data, int i, int len);
static void	get_rightend(t_data *data);

// trims all spaces from the right side of the map, trims \n
// may return malloc err
int	trim_rightend(t_data *data)
{
	int		len;
	int		i;
	char	*tmp;

	get_rightend(data);
	i = -1;
	while (data->input.map[++i] != NULL)
	{
		len = ft_strlen(data->input.map[i]);
		if (len == data->input.w_map)
			continue ;
		if (len < data->input.w_map)
			tmp = extend_line(data, i, len);
		else if (len > data->input.w_map)
			tmp = shorten_line(data, i, len);
		if (tmp == NULL)
			return (MALLOC_ERR);
		free(data->input.map[i]);
		data->input.map[i] = ft_strdup(tmp);
		if (data->input.map[i] == NULL)
			return (MALLOC_ERR);
		free(tmp);
	}
	return (SUCCESS);
}

// find the rightmost end of the lines in the map array
// saves map width;
static void	get_rightend(t_data *data)
{
	int	max_end;
	int	len;
	int	i;

	max_end = 0;
	i = -1;
	while (data->input.map[++i] != NULL)
	{
		len = ft_strlen(data->input.map[i]);
		while (data->input.map[i][len - 1] == ' ')
			len--;
		if (max_end < len)
			max_end = len;
	}
	data->input.w_map = max_end;
}

// fills line with spaces at it's right end
static char	*extend_line(t_data *data, int i, int len)
{
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (data->input.w_map + 1));
	tmp[data->input.w_map] = '\0';
	if (tmp == NULL)
		return (NULL);
	j = -1;
	while (++j < len)
		tmp[j] = data->input.map[i][j];
	while (j < data->input.w_map)
		tmp[j++] = ' ';
	tmp[j] = '\0';
	return (tmp);
}

// trims line spaces from it's right end
static char	*shorten_line(t_data *data, int i, int len)
{
	char	*tmp;

	while (len > data->input.w_map)
		len--;
	tmp = ft_substr(data->input.map[i], 0, len);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
