/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:40:14 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/18 21:38:29 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void		draw_walls(t_data *data);
static void	wall_orient(t_data *data, t_ray *ray);
static void	draw_vertical(t_data *data, t_ray *ray, int u);
static void	set_ords(int *ord_top, int *ord_bottom, t_data *data, t_ray *ray);

// STEP: FROM ANGLE + (+1/2)FOV_R TO ANGLE - (-1/2)FOV_R -
// step depending on window size - one ray per pixel
void	draw_walls(t_data *data)
{
	t_ray	ray;
	float	curr_angle;
	float	step;
	int		u;

	curr_angle = data->player.angle_r + deg_to_rad(FOV / 2);
	step = deg_to_rad(FOV) / data->mlx->width;
	u = 0;
	while (u < data->mlx->width)
	{
		ray.cos_angle = cosf(curr_angle);
		ray.sin_angle = sinf(curr_angle);
		ray.cos_angle_diff = fabsf(cosf(curr_angle - data->player.angle_r));
		cast_rays(data, &ray);
		wall_orient(data, &ray);
		draw_vertical(data, &ray, u);
		draw_miniray(data, &ray);
		curr_angle -= step;
		u++;
	}
}

// Wall orientation
static void	wall_orient(t_data *data, t_ray *ray)
{
	if (ray->corr_dist < 0)
	{
		ray->distance *= -1;
		ray->corr_dist *= -1;
		if (ray->step_x > 0)
			ray->wall_orient = EAST;
		else
			ray->wall_orient = WEST;
		ray->wall_x = data->player.y + ray->corr_dist * ray->sin_angle;
		ray->wall_x -= floor(ray->wall_x);
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_orient = SOUTH;
		else
			ray->wall_orient = NORTH;
		ray->wall_x = data->player.x + ray->corr_dist * ray->cos_angle;
		ray->wall_x -= floor(ray->wall_x);
	}
}

static void	draw_vertical(t_data *data, t_ray *ray, int u)
{
	int			v;
	int			height;
	int			ord_top;
	int			ord_bottom;
	t_texture	texture;

	height = data->mlx->height;
	ray->line_length = (int)((height * WALL_SIZE) / ray->corr_dist);
	set_ords(&ord_top, &ord_bottom, data, ray);
	// get appropriate texture for wall orientation
	texture.png = data->textures[ray->wall_orient];
		// can be NULL if no tex was uploaded unsucssesfully
	// calculate the x-coordinate on the texture
	texture.tex_x = calc_texture_x(ray, texture.png);
	v = ord_top;
	while (v < ord_bottom)
	{
		if (texture.png)
		{
			// calculate y-coordinate on the texture
			texture.tex_y = (v - ord_top) * texture.png->height
				/ ray->line_length;
			texture.color = sample_color(&texture);
			mlx_put_pixel(data->img, u, v, texture.color);
		}
		else
			mlx_put_pixel(data->img, u, v, use_default_clr(ray->wall_orient));
		v++;
	}
}

// setting ord_top and ord_bottom
static void	set_ords(int *ord_top, int *ord_bottom, t_data *data, t_ray *ray)
{
	int height;

	height = data->mlx->height;
	*ord_top = (height - ray->line_length) / 2;
	if (*ord_top < 0)
		*ord_top = 0;
	*ord_bottom = (height + ray->line_length) / 2;
	if (*ord_bottom >= height)
		*ord_bottom = height - 1;
}