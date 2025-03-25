/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:40:14 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/25 19:11:59 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

int			draw_walls(t_data *data);
static void	ray_init(t_data *data, t_ray *ray, int u);
static void	draw_vertical(t_data *data, t_ray *ray, int u);
static int	calc_wall_height(t_data *data, t_ray *ray);
static int	set_ords(int *ord_top, int *ord_bottom, t_data *data, t_ray *ray);

// STEP: FROM ANGLE + (+1/2)FOV_R TO ANGLE - (-1/2)FOV_R -
// we use the arctan because the angle step is not uniform - one ray per pixel
int	draw_walls(t_data *data)
{
	t_ray	ray;
	int		u;

	u = 0;
	data->miniray = malloc(data->mlx->width * sizeof(t_miniray));
	if (data->miniray == NULL) 
		return (MALLOC_ERR);
	while (u < data->mlx->width)
	{
		ray_init(data, &ray, u);
		cast_rays(data, &ray);
		wall_orient(data, &ray);
		draw_vertical(data, &ray, u);
		save_miniray(data, &ray, u);
		u++;
	}
	return (0);
}

static void	ray_init(t_data *data, t_ray *ray, int u)
{
	float	proj_plane_w;
	float	proj_plane_d;
	float	screen_x;

	proj_plane_d = 1.0f;
	proj_plane_w = 2.0f * proj_plane_d * tanf(deg_to_rad(FOV / 2));
	screen_x = 2.0f * u / data->mlx->width - 1.0f;
	ray->curr_arctan = -atan2f(screen_x * proj_plane_w / 2, proj_plane_d);
	ray->curr_angle = data->player.angle_r + ray->curr_arctan;
	ray->curr_angle = fmodf(ray->curr_angle, 2 * M_PI);
	ray->cos_angle = cosf(ray->curr_angle);
	ray->sin_angle = sinf(ray->curr_angle);
	ray->cos_angle_diff = fabsf(cosf(ray->curr_angle - data->player.angle_r));
}

static void	draw_vertical(t_data *data, t_ray *ray, int u)
{
	int			v;
	int			ord_top;
	int			ord_bottom;
	t_texture	t;

	ray->line_length = calc_wall_height(data, ray);
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

static int	calc_wall_height(t_data *data, t_ray *ray)
{
	float		vert_fov;
	float		window_ratio;
	float		wall_height;

	window_ratio = (float)data->mlx->width / (float)data->mlx->height;
	vert_fov = 2 * atan(tan(deg_to_rad(FOV / 2)) / window_ratio);
	wall_height = data->mlx->height / (2 * ray->corr_dist * tan(vert_fov / 2));
	return ((int)(wall_height));
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
