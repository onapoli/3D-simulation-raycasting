/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:21:05 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 18:11:54 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "reader.h"

int		free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
	return (0);
}

int		free_sprites(t_sprite **sprites)
{
	t_sprite	*current;
	t_sprite	*next;

	current = *sprites;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*sprites = 0;
	return (0);
}

int		ft_strcmp(char *str_1, char *str_2)
{
	int	i;

	if (ft_strlen(str_1) != ft_strlen(str_2))
		return (0);
	i = 0;
	while (str_1[i])
	{
		if (str_1[i] != str_2[i])
			return (0);
		i++;
	}
	return (1);
}

void	set_default_level_values(t_session *session)
{
	session->fov = deg_2_rad(60);
	session->level.cell_length = 64;
	session->level.wall_height = 64;
}

void	check_minimum_args(int argc)
{
	if (argc == 1)
	{
		write(1, "Error\nArguments missing when executing program.\n",
		sizeof("Error\nArguments missing when executing program.\n"));
		exit(EXIT_FAILURE);
	}
}
