/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:06:11 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/22 13:13:31 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	deg_to_rad(int nb);
float	rad_to_deg(float nb);

float	deg_to_rad(int nb)
{
	return (nb * (2 * M_PI) / 360.0);
}

float	rad_to_deg(float nb)
{
	return (nb / (2 * M_PI) * 360.0);
}
