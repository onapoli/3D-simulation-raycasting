/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 10:46:11 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 13:10:11 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	case_vertical_intersect(double vertical_intersect_coord[2],
t_ray *ray, t_session *session)
{
	ray->wall_pos = vertical_intersect_coord[1];
	return (get_2_point_distance(session->player.x_pos,
	session->player.y_pos, vertical_intersect_coord[0],
	vertical_intersect_coord[1]));
}

static double	case_no_wall_intersect(double vertical_intersect_coord[2],
double horizontal_intersect_coord[2], t_ray *ray, t_session *session)
{
	double vertical_intersect_distance;
	double horizontal_intersect_distance;

	vertical_intersect_distance =
	get_2_point_distance(session->player.x_pos, session->player.y_pos,
	vertical_intersect_coord[0], vertical_intersect_coord[1]);
	horizontal_intersect_distance =
	get_2_point_distance(session->player.x_pos, session->player.y_pos,
	horizontal_intersect_coord[0], horizontal_intersect_coord[1]);
	if (vertical_intersect_distance < horizontal_intersect_distance)
	{
		ray->wall_intersect = 1;
		ray->wall_pos = vertical_intersect_coord[1];
		return (vertical_intersect_distance);
	}
	ray->wall_intersect = 2;
	ray->wall_pos = horizontal_intersect_coord[0];
	return (horizontal_intersect_distance);
}

static double	get_wall_distance(t_ray *ray, t_session *session)
{
	double	vertical_intersect_coord[2];
	double	horizontal_intersect_coord[2];
	size_t	cell_position[2];

	ray->wall_intersect = 0;
	get_cell(cell_position, session->player.x_pos, session->player.y_pos,
	session->level.cell_length);
	if (!vertical_wall(vertical_intersect_coord, ray->angle, cell_position[1],
	session))
		ray->wall_intersect = 2;
	if (!horizontal_wall(horizontal_intersect_coord, ray->angle,
	cell_position[0], session))
		ray->wall_intersect = 1;
	if (!(ray->wall_intersect))
	{
		return (case_no_wall_intersect(vertical_intersect_coord,
		horizontal_intersect_coord, ray, session));
	}
	if (ray->wall_intersect == 1)
		return
		(case_vertical_intersect(vertical_intersect_coord, ray, session));
	ray->wall_pos = horizontal_intersect_coord[0];
	return (get_2_point_distance(session->player.x_pos, session->player.y_pos,
	horizontal_intersect_coord[0], horizontal_intersect_coord[1]));
}

int				raycaster(t_session *session, double *z_buffer)
{
	double	initial_ray_angle;
	double	increment_angle;
	int		i;
	t_ray	*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (-1);
	initial_ray_angle = normalize_angle(session->player.angle -
	(session->fov / 2));
	increment_angle = session->fov / session->win_width;
	i = 0;
	while (i < session->win_width)
	{
		ray->angle = normalize_angle(initial_ray_angle + (increment_angle * i));
		ray->wall_distance = get_wall_distance(ray, session);
		ray->wall_distance *= cos(normalize_angle(session->player.angle -
		ray->angle));
		ray->wall_pixels = get_wall_pixels(session->level.wall_height,
		ray->wall_distance, session->projection_distance);
		draw_wall_texture(session, i, ray);
		z_buffer[i] = ray->wall_distance;
		i++;
	}
	free(ray);
	return (0);
}
