/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:56:14 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/14 14:36:08 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static mlx_texture_t	*load_png(t_data *data, char *path);

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->img = NULL;
	data->input.map = NULL;
	data->input.w_map = -1;
	data->input.h_map = -1;
	data->input.so = NULL;
	data->input.we = NULL;
	data->input.ea = NULL;
	data->input.no = NULL;
	data->input.floor = -1;
	data->input.sky = -1;
	data->input.play_x = -1;
	data->input.play_y = -1;
	data->input.cardinal = '0';
	data->input.doors_nbr = -1;
	data->player.x = 0;
	data->player.y = 0;
	data->player.angle_r = 0;
	data->textures = NULL;
}

void	load_textures(t_data *data)
{
	data->textures = (mlx_texture_t **) malloc(sizeof(mlx_texture_t *) * 4);
	if (!data->textures)
		exit_err(data, "Malloc", MALLOC_ERR);
	data->textures[NORTH] = load_png(data, data->input.no);
	data->textures[SOUTH] = load_png(data, data->input.so);
	data->textures[WEST] = load_png(data, data->input.we);
	data->textures[EAST] = load_png(data, data->input.ea);
}

//load png texture. if file is missing or corrupted will err msg and return null
static mlx_texture_t	*load_png(t_data *data, char *path)
{
	mlx_texture_t	*texture;

	(void)data;
	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Failed to load texture: %s\n", path);
		return (NULL);
	}
	return (texture);
}
