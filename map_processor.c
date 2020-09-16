/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:08:29 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/03 13:58:51 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int		validate_map_chars(char *map_line)
{
	int	i;

	if (!map_line)
		return (-1);
	i = 0;
	while (map_line[i])
	{
		if (map_line[i] != '0' && map_line[i] != '1' && map_line[i] != '2' &&
		map_line[i] != ' ' && map_line[i] != 'N' && map_line[i] != 'S' &&
		map_line[i] != 'W' && map_line[i] != 'E')
			return (-1);
		i++;
	}
	if (i == 0)
		return (-1);
	return (0);
}

int				add_map_line(char *map_line, t_map_line **map_lines)
{
	t_map_line	*new_map_line;
	t_map_line	**current_map_line;

	if (validate_map_chars(map_line) == -1)
		return (-1);
	if (!(new_map_line = malloc(sizeof(t_map_line))))
		return (-1);
	new_map_line->next = 0;
	new_map_line->line = ft_strdup(map_line);
	current_map_line = map_lines;
	while (*current_map_line)
		current_map_line = &(*current_map_line)->next;
	*current_map_line = new_map_line;
	return (0);
}
