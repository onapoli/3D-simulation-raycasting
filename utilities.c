/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:35:41 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:50:28 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_2_rad(int degrees)
{
	double radians;

	radians = (degrees * (2 * M_PI)) / 360;
	return (radians);
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += deg_2_rad(360);
	if (angle >= deg_2_rad(360))
		angle -= deg_2_rad(360);
	return (angle);
}

double	get_2_point_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int		get_direction(double angle, char target)
{
	if (target == 'x')
	{
		if (angle < deg_2_rad(90) || angle > deg_2_rad(270))
			return (1);
		else
			return (0);
	}
	else if (target == 'y')
	{
		if (angle < deg_2_rad(180))
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}

int		get_wall_pixels(int wall_height, double wall_distance,
double projection_plane_distance)
{
	return ((int)floor((wall_height / wall_distance) *
	projection_plane_distance));
}
