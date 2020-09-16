/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:47:43 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/10 18:20:26 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	store_player_data(size_t column, size_t row, char map_element,
t_session *session)
{
	if (session->player.x_pos || session->player.y_pos ||
	session->player.angle)
		return (-1);
	session->player.x_pos = (column * session->level.cell_length) +
	(session->level.cell_length / 2);
	session->player.y_pos = (row * session->level.cell_length) +
	(session->level.cell_length / 2);
	if (map_element == 'N')
		session->player.angle = deg_2_rad(270);
	else if (map_element == 'E')
		session->player.angle = 0;
	else if (map_element == 'S')
		session->player.angle = deg_2_rad(90);
	else if (map_element == 'W')
		session->player.angle = deg_2_rad(180);
	else
		return (-1);
	return (0);
}

static int	store_sprite(size_t column, size_t row, t_session *session)
{
	t_sprite	*new_sprite;
	t_sprite	**current_sprite;

	if (!(new_sprite = malloc(sizeof(t_sprite))))
		return (-1);
	new_sprite->data.x_pos = (column * session->level.cell_length) +
	(session->level.cell_length / 2);
	new_sprite->data.y_pos = (row * session->level.cell_length) +
	(session->level.cell_length / 2);
	new_sprite->next = 0;
	current_sprite = &(session)->level.sprites;
	if (!(*current_sprite))
	{
		*current_sprite = new_sprite;
		return (0);
	}
	while ((*current_sprite)->next)
		current_sprite = &(*current_sprite)->next;
	(*current_sprite)->next = new_sprite;
	return (0);
}

static int	validate_line_letter_sprite(char **map, size_t row, size_t column,
t_session *session)
{
	char	*element;

	element = &map[row][column];
	if (*element == 'N' || *element == 'S' || *element == 'W' ||
	*element == 'E' || *element == '2')
	{
		if (*element == '2')
		{
			if (store_sprite(column, row, session) == -1)
				return (-1);
		}
		else
		{
			if (store_player_data(column, row, *element, session) == -1)
				return (-1);
		}
		*element = '0';
	}
	return (0);
}

static int	validate_line(char **map, size_t row, t_session *session,
size_t prev_line_limits[2])
{
	size_t	i;
	int		first_num;
	size_t	this_line_limits[2];

	i = 0;
	first_num = 0;
	while (map[row][i])
	{
		if (validate_line_letter_sprite(map, row, i, session) == -1)
			return (-1);
		if (validate_line_zeroes(map, row, i, prev_line_limits) == -1)
			return (-1);
		if (map[row][i] != ' ')
		{
			if (validate_line_nospace(i, map[row][i], &first_num,
			this_line_limits) == -1)
				return (-1);
		}
		i++;
	}
	if (map[row][this_line_limits[1]] != '1' || !first_num)
		return (-1);
	prev_line_limits[0] = this_line_limits[0];
	prev_line_limits[1] = this_line_limits[1];
	return (0);
}

int			validate_map(t_session *session)
{
	char	**map;
	size_t	i;
	size_t	line_limits[2];

	if (!session->level.map[0])
		return (-1);
	map = session->level.map;
	i = 0;
	if (validate_first_line(map, i, line_limits) == -1)
		return (-1);
	i++;
	while (map[i])
	{
		if (!map[i + 1])
			break ;
		if (validate_line(map, i, session, line_limits) == -1)
			return (-1);
		i++;
	}
	if (validate_last_line(map, i) == -1 || !(session->player.x_pos))
		return (-1);
	return (0);
}
