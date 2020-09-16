/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 20:44:01 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:46:30 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_sprite_visibility(double sprite_angle, double player_angle,
double fov)
{
	double	difference;

	difference = player_angle - sprite_angle;
	if (difference > deg_2_rad(180) || difference < deg_2_rad(-180))
	{
		if (difference > 0)
			difference -= deg_2_rad(360);
		else
			difference += deg_2_rad(360);
	}
	if (fabs(difference) > (fov / 2) + deg_2_rad(15))
		return (0);
	return (1);
}

double	get_sprite_angle(double s_x_pos, double s_y_pos, double p_x_pos,
double p_y_pos)
{
	double sprite_angle;

	sprite_angle = atan2(s_y_pos - p_y_pos, s_x_pos - p_x_pos);
	return (normalize_angle(sprite_angle));
}

int		sprite_screen_midpoint(double player_angle, double sprite_angle,
double fov, int win_width)
{
	double	initial_ray_angle;
	double	angle_increment;
	double	x_pixel;

	initial_ray_angle = player_angle - (fov / 2);
	angle_increment = fov / win_width;
	if (fabs(player_angle - sprite_angle) < deg_2_rad(180))
		x_pixel = (sprite_angle - initial_ray_angle) / angle_increment;
	else if (player_angle - sprite_angle < 0)
		x_pixel = (sprite_angle -
		(normalize_angle(initial_ray_angle))) / angle_increment;
	else
		x_pixel = (sprite_angle -
		(initial_ray_angle - deg_2_rad(360))) / angle_increment;
	return ((int)round(x_pixel));
}
