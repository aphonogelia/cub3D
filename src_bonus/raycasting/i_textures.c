/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:43:48 by ilazar            #+#    #+#             */
/*   Updated: 2025/04/01 19:10:37 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

// calculate the x-coordinate on the texture
int	calc_texture_x(t_ray *ray, mlx_texture_t *texture)
{
	int	tex_x;

	if (texture == NULL)
		return (0);
	tex_x = (int)(ray->wall_x * texture->width) % texture->width;
	if ((ray->wall_orient == EAST && ray->step_x > 0)
		|| (ray->wall_orient == NORTH && ray->step_y > 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

// calculate the y-coordinate on the texture
// sample pixel from texture and correct bytes order
uint32_t	sample_color(t_texture *texture)
{
	uint32_t	color;
	uint32_t	raw_color;

	raw_color = ((uint32_t *)texture->png->pixels)[texture->tex_y
		* texture->png->width + texture->tex_x];
	color = ((raw_color & 0xFF) << 24) 
		| ((raw_color & 0xFF00) << 8) 
		| ((raw_color & 0xFF0000) >> 8) 
		| ((raw_color & 0xFF000000) >> 24);
	return (color);
}

// in case of failure to load a texture use default colors
int	use_default_clr(int wall_orient)
{
	int	clr;

	clr = BLACK;
	if (wall_orient == EAST)
		clr = CLR_EAST;
	if (wall_orient == WEST)
		clr = CLR_WEST;
	if (wall_orient == NORTH)
		clr = CLR_NORTH;
	if (wall_orient == SOUTH)
		clr = CLR_SOUTH;
	if (wall_orient == DOOR_TEXTURE)
		clr = CLR_DOOR;
	return (clr);
}

void	clean_textures(t_data *data)
{
	int	i;

	i = -1;
	if (data->textures)
	{
		while (++i < 5)
		{
			if (data->textures[i])
				mlx_delete_texture(data->textures[i]);
		}
		free(data->textures);
		data->textures = NULL;
	}
}
