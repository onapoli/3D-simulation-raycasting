/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_first_last_lines.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:51:52 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:57:27 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	first_line_process_space(char **map, size_t row,
size_t current_column)
{
	size_t	j;

	j = row;
	while (map[j])
	{
		if (map[j][current_column] != ' ' && map[j][current_column] != '1')
			return (-1);
		if (map[j][current_column] == '1')
			break ;
		j++;
	}
	return (0);
}

static void	first_line_process_nospace(size_t column,
size_t this_line_limits[2], int *first_num)
{
	if (!(*first_num))
	{
		this_line_limits[0] = column;
		*first_num = 1;
	}
	this_line_limits[1] = column;
}

static int	first_line_checks(char **map, size_t row,
size_t this_line_limits[2])
{
	size_t	i;
	int		first_num;

	i = 0;
	first_num = 0;
	while (map[row][i])
	{
		if (map[row][i] != '1' && map[row][i] != ' ')
			return (-1);
		if (map[row][i] == ' ')
		{
			if (first_line_process_space(map, row, i) == -1)
				return (-1);
		}
		else
			first_line_process_nospace(i, this_line_limits, &first_num);
		i++;
	}
	if (!first_num)
		return (-1);
	return (0);
}

int			validate_first_line(char **map, size_t row, size_t line_limits[2])
{
	size_t	this_line_limits[2];

	if (first_line_checks(map, row, this_line_limits) == -1)
		return (-1);
	line_limits[0] = this_line_limits[0];
	line_limits[1] = this_line_limits[1];
	return (0);
}

int			validate_last_line(char **map, size_t row)
{
	size_t		i;
	long long	j;

	i = 0;
	while (map[row][i])
	{
		if (map[row][i] != '1' && map[row][i] != ' ')
			return (-1);
		if (map[row][i] == ' ')
		{
			j = row;
			while (j >= 0)
			{
				if (map[j][i] != ' ' && map[j][i] != '1')
					return (-1);
				if (map[j][i] == '1')
					break ;
				j--;
			}
		}
		i++;
	}
	return (0);
}
