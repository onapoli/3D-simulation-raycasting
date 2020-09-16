/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_wall_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:43:02 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/03 13:12:49 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	vertical_wall_iter(double angle, double intersect_coord[2],
t_session *session, size_t cell_position[2])
{
	double	slope;

	slope = tan(angle);
	while (!check_wall(session->level.map, cell_position[0], cell_position[1]))
	{
		if (get_direction(angle, 'x'))
			intersect_coord[0] += session->level.cell_length;
		else
			intersect_coord[0] -= session->level.cell_length;
		if (slope == 0)
		{
			get_cell(cell_position, intersect_coord[0], intersect_coord[1],
			session->level.cell_length);
			continue;
		}
		intersect_coord[1] = get_vertical_intersection(slope,
		intersect_coord[0], session->player.x_pos, session->player.y_pos);
		if (!get_direction(angle, 'y'))
			intersect_coord[1] = ceil(intersect_coord[1]);
		get_cell(cell_position, intersect_coord[0], intersect_coord[1],
		session->level.cell_length);
	}
	return (0);
}

static int	horizontal_wall_iter(double angle, double intersect_coord[2],
t_session *session, size_t cell_position[2])
{
	double	slope;

	slope = tan(angle);
	while (!check_wall(session->level.map, cell_position[0], cell_position[1]))
	{
		if (get_direction(angle, 'y'))
			intersect_coord[1] += session->level.cell_length;
		else
			intersect_coord[1] -= session->level.cell_length;
		if (angle == deg_2_rad(90) || angle == deg_2_rad(270))
		{
			get_cell(cell_position, intersect_coord[0], intersect_coord[1],
			session->level.cell_length);
			continue;
		}
		intersect_coord[0] = get_horizontal_intersection(slope,
		intersect_coord[1], session->player.x_pos, session->player.y_pos);
		if (!get_direction(angle, 'x'))
			intersect_coord[0] = ceil(intersect_coord[0]);
		get_cell(cell_position, intersect_coord[0], intersect_coord[1],
		session->level.cell_length);
	}
	return (0);
}

int			vertical_wall(double intersect_coord[2], double angle,
size_t cell_column, t_session *session)
{
	double	slope;
	size_t	cell_position[2];

	if (angle == deg_2_rad(90) || angle == deg_2_rad(270))
		return (0);
	slope = tan(angle);
	intersect_coord[0] = get_axis_parallel(session->level.cell_length,
	cell_column, get_direction(angle, 'x'));
	if (slope == 0)
		intersect_coord[1] = session->player.y_pos;
	else
		intersect_coord[1] = get_vertical_intersection(slope,
		intersect_coord[0], session->player.x_pos, session->player.y_pos);
	if (!get_direction(angle, 'y'))
		intersect_coord[1] = ceil(intersect_coord[1]);
	get_cell(cell_position, intersect_coord[0], intersect_coord[1],
	session->level.cell_length);
	if (!check_wall(session->level.map, cell_position[0], cell_position[1]))
	{
		vertical_wall_iter(angle, intersect_coord, session, cell_position);
		return (1);
	}
	return (1);
}

int			horizontal_wall(double intersect_coord[2], double angle,
size_t cell_row, t_session *session)
{
	double	slope;
	size_t	cell_position[2];

	slope = tan(angle);
	if (slope == 0)
		return (0);
	intersect_coord[1] = get_axis_parallel(session->level.cell_length,
	cell_row, get_direction(angle, 'y'));
	if (angle == deg_2_rad(90) || angle == deg_2_rad(270))
		intersect_coord[0] = session->player.x_pos;
	else
		intersect_coord[0] = get_horizontal_intersection(slope,
		intersect_coord[1], session->player.x_pos, session->player.y_pos);
	if (!get_direction(angle, 'x'))
		intersect_coord[0] = ceil(intersect_coord[0]);
	get_cell(cell_position, intersect_coord[0], intersect_coord[1],
	session->level.cell_length);
	if (!check_wall(session->level.map, cell_position[0], cell_position[1]))
	{
		horizontal_wall_iter(angle, intersect_coord, session, cell_position);
		return (1);
	}
	return (1);
}
