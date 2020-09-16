/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:38:56 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/03 12:48:59 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	fill_map(char **map, t_map_line *map_lines)
{
	t_map_line	*element;
	size_t		i;

	element = map_lines;
	i = 0;
	while (element)
	{
		map[i] = ft_strdup(element->line);
		element = element->next;
		i++;
	}
	return (0);
}

static int	get_map_dimension(t_map_line *map_lines, size_t *row_length)
{
	t_map_line	*element;
	size_t		i;

	element = map_lines;
	i = 0;
	while (element)
	{
		element = element->next;
		i++;
	}
	*row_length = i;
	return (0);
}

int			generate_map(char ***map, t_map_line *map_lines)
{
	size_t	row_length;

	get_map_dimension(map_lines, &row_length);
	if (!(*map = (char **)malloc(sizeof(char *) * (row_length + 1))))
		return (-1);
	(*map)[row_length] = 0;
	if (fill_map(*map, map_lines) == -1)
		return (-1);
	return (0);
}
