/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:08:48 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 13:01:39 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "reader.h"

static int		free_map_lines(t_map_line **map_lines)
{
	t_map_line	*current;
	t_map_line	*next;

	current = *map_lines;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
	*map_lines = 0;
	return (0);
}

static int		data_missing(t_session *session)
{
	if (!session->win_width || !session->win_height ||
	!session->textures[0].path || !session->textures[1].path ||
	!session->textures[2].path || !session->textures[3].path ||
	!session->sprite_texture.path || !session->level.floor_color ||
	!session->level.ceiling_color)
		return (1);
	return (0);
}

static int		generate_validate_map(t_session *session, t_map_line *map_lines)
{
	if (generate_map(&(session)->level.map, map_lines) == -1)
	{
		write(1, "Error\ncould not generate map.\n", 30);
		return (-1);
	}
	if (validate_map(session) == -1)
	{
		if (map_lines)
			free_map_lines(&map_lines);
		write(1, "Error\ninvalid map.\n", 19);
		return (-1);
	}
	return (0);
}

static int		get_map(int fd, int *line_result, t_map_line **map_lines,
t_session *session)
{
	char	*line;

	line = 0;
	while ((*line_result = get_next_line(fd, &line)) != -1 && *line_result)
	{
		if (data_missing(session))
		{
			if (send_to_process_data(line, session) == -1)
				return (-1);
		}
		else
		{
			if (!line[0] && !map_lines[0])
				continue;
			if (!line[0] || add_map_line(line, map_lines) == -1)
			{
				free(line);
				write(1, "Error\nBad map data in .cub file.\n", 33);
				return (-1);
			}
		}
	}
	free(line);
	return (0);
}

int				ft_read_file(t_session *session, char *file_path)
{
	int			fd;
	int			line_result;
	t_map_line	*map_lines;

	map_lines = 0;
	if (ft_open_file(&fd, file_path) == -1)
		return (-1);
	if (get_map(fd, &line_result, &map_lines, session) == -1)
	{
		free_map_lines(&map_lines);
		return (-1);
	}
	if (line_result == -1)
	{
		write(1, "Error\nFile read operation failed.\n", 34);
		return (-1);
	}
	close(fd);
	if (generate_validate_map(session, map_lines) == -1)
		return (-1);
	free_map_lines(&map_lines);
	return (0);
}
