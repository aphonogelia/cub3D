/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:51:29 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/24 19:18:47 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void			mouse_callback(double xpos, double ypos, void *param);
void			check_mouse_inactivity(t_data *data);
static double	define_sens(t_data *data, double xpos);
static void		player_angle(t_data *data, double xpos, double sens);
static int		prepare_callback(t_data *data, double xpos);

void	mouse_callback(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	sens;

	data = (t_data *)param;
	if (prepare_callback(data, xpos))
		return ;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	if (xpos <= 10)
	{
		mlx_set_mouse_pos(data->mlx, data->mlx->width - 15, ypos);
		data->mouse.last_x = data->mlx->width - 15;
		return ;
	}
	if (xpos >= data->mlx->width - 10)
	{
		mlx_set_mouse_pos(data->mlx, 15, ypos);
		data->mouse.last_x = 15;
		return ;
	}
	sens = define_sens(data, xpos);
	player_angle(data, xpos, sens);
	data->mouse.last_x = xpos;
}

void	check_mouse_inactivity(t_data *data)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - data->mouse.cursor_last_moved > 0.1)
		data->flag_refresh = false;
}

static int	prepare_callback(t_data *data, double xpos)
{
	if (data->screen.is_welcome)
		return (1);
	data->mouse.cursor_last_moved = mlx_get_time();
	if (data->mouse.first_call)
	{
		data->mouse.last_x = xpos;
		data->mouse.first_call = false;
		return (1);
	}
	data->flag_refresh = true;
	return (0);
}

static double	define_sens(t_data *data, double xpos)
{
	if (xpos < 20 || xpos > data->mlx->width - 20)
		return (MOUSE_SENS * 2.0);
	else
		return (MOUSE_SENS);
}

static void	player_angle(t_data *data, double xpos, double sens)
{
	double	delta_x;

	delta_x = xpos - data->mouse.last_x;
	data->player.angle_r -= delta_x * sens;
	data->player.angle_r = fmodf(data->player.angle_r, 2 * M_PI);
	if (data->player.angle_r < 0)
		data->player.angle_r += 2 * M_PI;
}
