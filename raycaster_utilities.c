/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 12:06:01 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:31:26 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_horizontal_intersection(double slope, double y_intersect,
double x_pos, double y_pos)
{
	return (((y_intersect - y_pos) / slope) + x_pos);
}

double	get_vertical_intersection(double slope, double x_intersect,
double x_pos, double y_pos)
{
	return (slope * (x_intersect - x_pos) + y_pos);
}

double	get_axis_parallel(int cell_length, int cell_position, int dir)
{
	double	parallel_coord;

	parallel_coord = (cell_position + dir) * cell_length;
	if (dir == 0)
		parallel_coord--;
	return (parallel_coord);
}
