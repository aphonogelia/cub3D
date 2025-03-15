/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:40:14 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/15 16:14:38 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		draw_walls(t_data *data);
static void	wall_orient(t_data *data, t_ray *ray);
static void	draw_vertical(t_data *data, t_ray *ray, int u);
static int	set_ords(int *ord_top, int *ord_bottom, t_data *data, t_ray *ray);

// STEP: FROM ANGLE + (+1/2)FOV_R TO ANGLE - (-1/2)FOV_R - 
// step depending on window size - one ray per pixel
void	draw_walls(t_data *data)
{
	t_ray	ray;
	int		u;

	ray.curr_angle = data->player.angle_r + degree_to_rad(FOV / 2);
	ray.step = degree_to_rad(FOV) / data->mlx->width;
	u = 0;
	while (u < data->mlx->width)
	{
		ray.cos_angle = cosf(ray.curr_angle);
		ray.sin_angle = sinf(ray.curr_angle);
		ray.cos_angle_diff = fabsf(cosf(ray.curr_angle - data->player.angle_r));
		cast_rays(data, &ray);
		wall_orient(data, &ray);
		draw_vertical(data, &ray, u);
		ray.curr_angle -= ray.step;
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
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_orient = SOUTH;
		else 
			ray->wall_orient = NORTH;
		ray->wall_x = data->player.x + ray->corr_dist * ray->cos_angle;
	}
	ray->wall_x -= floor(ray->wall_x);
}

static void	draw_vertical(t_data *data, t_ray *ray, int u)
{
	int			v;
	int			ord_top;
	int			ord_bottom;
	t_texture	t;

	ray->line_length = (int)((data->mlx->height * WALL_SIZE) / ray->corr_dist);
	t.text_top = set_ords(&ord_top, &ord_bottom, data, ray);
	t.png = data->textures[ray->wall_orient];
	t.tex_x = calc_texture_x(ray, t.png);
	v = ord_top;
	while (v < ord_bottom)
	{
		if (t.png)
		{
			t.text_pos = (float)(v - ord_top + t.text_top) / ray->line_length;
			t.tex_y = (int)(t.text_pos * t.png->height);
			t.color = sample_color(&t);
			mlx_put_pixel(data->img, u, v, t.color);
		}
		else
			mlx_put_pixel(data->img, u, v, use_default_clr(ray->wall_orient));
		v++;
	}
}

//setting ord_top and ord_bottom
static int	set_ords(int *ord_top, int *ord_bottom, t_data *data, t_ray *ray)
{
	int	height;
	int	text_top;

	height = data->mlx->height;
	*ord_bottom = (height + ray->line_length) / 2;
	if (*ord_bottom >= height)
		*ord_bottom = height - 1;
	*ord_top = (height - ray->line_length) / 2;
	text_top = 0;
	if (*ord_top < 0)
	{
		text_top = -*ord_top;
		*ord_top = 0;
	}
	return (text_top);
}
