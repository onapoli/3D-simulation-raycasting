/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:58:58 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 14:11:16 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	add_color(int data_type, char *data, t_session *session)
{
	int				i;
	int				number;
	int				rgb[3];
	unsigned long	color;

	i = 0;
	if ((number = mini_atoi(data, &i, ',')) == -1)
		return (-1);
	rgb[0] = number;
	if (get_rgb(data, &i, &(rgb[1])) == -1)
		return (-1);
	if (get_rgb(data, &i, &(rgb[2])) == -1)
		return (-1);
	if (unify_rgb(&color, rgb) == -1)
		return (-1);
	if (data_type == 7)
		session->level.floor_color = color;
	if (data_type == 8)
		session->level.ceiling_color = color;
	return (0);
}

static int	add_path(int data_type, char *data, t_session *session)
{
	int	valid;

	valid = validate_path(data);
	if (!valid)
		return (-1);
	if (data_type == 2)
		session->textures[0].path = ft_strdup(data);
	if (data_type == 3)
		session->textures[2].path = ft_strdup(data);
	if (data_type == 4)
		session->textures[3].path = ft_strdup(data);
	if (data_type == 5)
		session->textures[1].path = ft_strdup(data);
	if (data_type == 6)
		session->sprite_texture.path = ft_strdup(data);
	return (0);
}

static int	add_resolution(char *data, t_session *session)
{
	int	i;
	int	number;

	i = 0;
	if ((number = mini_atoi(data, &i, ' ')) == -1)
		return (-1);
	session->win_width = number;
	while (data[i] == ' ')
		i++;
	if (!data[i])
		return (-1);
	if ((number = mini_atoi(data, &i, ' ')) == -1)
		return (-1);
	session->win_height = number;
	if (!session->win_width || !session->win_height)
		return (-1);
	return (0);
}

int			add_data(int data_type, char *data, t_session *session)
{
	int	i;

	i = 0;
	while (data[i] == ' ')
		i++;
	if (!data[i])
		return (-1);
	if (data_type == 1)
	{
		if (add_resolution(&data[i], session) == -1)
			return (-1);
	}
	if (data_type > 1 && data_type < 7)
	{
		if (add_path(data_type, &data[i], session) == -1)
			return (-1);
	}
	if (data_type > 6)
	{
		if (add_color(data_type, &data[i], session) == -1)
			return (-1);
	}
	return (0);
}
