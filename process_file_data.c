/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:48:58 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 14:40:25 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	check_repeat_data(int data_type, t_session *session)
{
	if (data_type == 1 && session->file_data.r)
		return (-1);
	else if (data_type == 2 && session->file_data.no)
		return (-1);
	else if (data_type == 3 && session->file_data.so)
		return (-1);
	else if (data_type == 4 && session->file_data.we)
		return (-1);
	else if (data_type == 5 && session->file_data.ea)
		return (-1);
	else if (data_type == 6 && session->file_data.s)
		return (-1);
	else if (data_type == 7 && session->file_data.f)
		return (-1);
	else if (data_type == 8 && session->file_data.c)
		return (-1);
	return (0);
}

static int	register_data_type(int data_type, t_session *session)
{
	if (check_repeat_data(data_type, session) == -1)
		return (-1);
	if (data_type == 1)
		session->file_data.r = 1;
	else if (data_type == 2)
		session->file_data.no = 1;
	else if (data_type == 3)
		session->file_data.so = 1;
	else if (data_type == 4)
		session->file_data.we = 1;
	else if (data_type == 5)
		session->file_data.ea = 1;
	else if (data_type == 6)
		session->file_data.s = 1;
	else if (data_type == 7)
		session->file_data.f = 1;
	else if (data_type == 8)
		session->file_data.c = 1;
	return (0);
}

static int	check_data_type_nwe(int *data_type, char *data, int *position)
{
	if (data[*position] == 'N' || data[*position] == 'W' ||
	data[*position] == 'E')
	{
		if (data[*position] == 'N' && data[*position + 1] == 'O')
			*data_type = 2;
		else if (data[*position] == 'W' && data[*position + 1] == 'E')
			*data_type = 4;
		else if (data[*position] == 'E' && data[*position + 1] == 'A')
			*data_type = 5;
		else
			return (-1);
		*position += 1;
	}
	return (0);
}

static int	check_data_type(int *data_type, char *data, int *position)
{
	if (data[*position] != 'R' && data[*position] != 'N' &&
	data[*position] != 'S' && data[*position] != 'W' &&
	data[*position] != 'E' && data[*position] != 'F' && data[*position] != 'C')
		return (-1);
	if (data[*position] == 'R')
		*data_type = 1;
	if (check_data_type_nwe(data_type, data, position) == -1)
		return (-1);
	if (data[*position] == 'S')
	{
		if (data[*position + 1] == 'O')
		{
			*data_type = 3;
			*position += 1;
		}
		else
			*data_type = 6;
	}
	if (data[*position] == 'F')
		*data_type = 7;
	if (data[*position] == 'C')
		*data_type = 8;
	return (0);
}

int			process_data(char *line, t_session *session)
{
	int	i;
	int	data_type;

	i = 0;
	data_type = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (!data_type)
			{
				if (check_data_type(&data_type, line, &i) == -1 ||
				register_data_type(data_type, session) == -1)
					return (-1);
			}
			else
			{
				if (add_data(data_type, &line[i], session) == -1)
					return (-1);
				return (0);
			}
		}
		i++;
	}
	return (0);
}
