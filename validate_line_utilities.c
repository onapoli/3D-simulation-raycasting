/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:04:12 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/03 12:59:08 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

int				validate_line_nospace(size_t column, char element,
int *first_num, size_t this_line_limits[2])
{
	if (!(*first_num) && element != '1')
		return (-1);
	if (!(*first_num))
	{
		*first_num = 1;
		this_line_limits[0] = column;
	}
	this_line_limits[1] = column;
	return (0);
}

static int		validate_line_zero(char **map, size_t row, size_t column,
size_t prev_line_limits[2])
{
	if (prev_line_limits[0] > column || prev_line_limits[1] < column)
		return (-1);
	if (!map[row + 2])
	{
		if (ft_strlen(map[row + 1]) < column)
			return (-1);
		if (map[row + 1][column] != '1')
			return (-1);
	}
	return (0);
}

static int		validate_line_zero_space(char **map, size_t row, size_t column)
{
	if (map[row][column - 1] != '1' &&
	map[row][column - 1] != map[row][column])
		return (-1);
	if (ft_strlen(map[row - 1]) >= column)
	{
		if (map[row - 1][column] != '1' &&
		map[row - 1][column] != map[row][column])
			return (-1);
	}
	return (0);
}

int				validate_line_zeroes(char **map, size_t row, size_t column,
size_t prev_line_limits[2])
{
	if (map[row][column] == '0' || map[row][column] == ' ')
	{
		if (validate_line_zero_space(map, row, column) == -1)
			return (-1);
	}
	if (map[row][column] == '0')
	{
		if (validate_line_zero(map, row, column, prev_line_limits) == -1)
			return (-1);
	}
	return (0);
}
