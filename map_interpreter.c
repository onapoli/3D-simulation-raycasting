/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:54:01 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:03:34 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_cell(size_t cell[2], double x_coord, double y_coord, int cell_length)
{
	size_t	cell_row;
	size_t	cell_column;

	cell_row = (size_t)floor(y_coord / cell_length);
	cell_column = (size_t)floor(x_coord / cell_length);
	cell[0] = cell_row;
	cell[1] = cell_column;
	return (0);
}

int	check_wall(char **map, size_t row, size_t column)
{
	size_t	row_len;
	size_t	column_len;

	row_len = 0;
	while (map[row_len])
		row_len++;
	if (row >= row_len)
		return (-1);
	column_len = 0;
	while (map[row][column_len])
		column_len++;
	if (column >= column_len)
		return (-1);
	if (map[row][column] == '1' || map[row][column] == ' ')
		return (1);
	return (0);
}
