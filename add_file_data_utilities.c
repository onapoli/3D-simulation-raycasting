/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_data_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:05:52 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/14 17:15:11 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

int	mini_atoi(char *data, int *i, char delimiter)
{
	int number;
	int	digits;

	number = 0;
	digits = 0;
	while (data[*i] && data[*i] != delimiter)
	{
		if (data[*i] < '0' || data[*i] > '9')
			return (-1);
		if (digits >= 4)
			return (-1);
		if (number == 0)
			number = data[*i] - '0';
		else
			number = (number * 10) + (data[*i] - '0');
		*i += 1;
		digits++;
	}
	if (!digits)
		return (-1);
	return (number);
}

int	unify_rgb(unsigned long *color, int rgb[3])
{
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255 || rgb[0] < 0 ||
	rgb[1] < 0 || rgb[2] < 0)
		return (-1);
	if (rgb[0] == 0 && rgb[1] == 0 && rgb[2] == 0)
		rgb[0] = 1;
	*color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (0);
}

int	get_rgb(char *data, int *i, int *rgb)
{
	int number;

	while (data[*i] == ',' || data[*i] == ' ')
		*i += 1;
	if (!data[*i])
		return (-1);
	if ((number = mini_atoi(data, i, ',')) == -1)
		return (-1);
	*rgb = number;
	return (0);
}

int	validate_path(char *data)
{
	size_t	i;
	int		valid;

	i = 0;
	valid = 0;
	while (data[i])
	{
		if (data[i] == '.' && data[i + 1] == 'x' && data[i + 2] == 'p' &&
		data[i + 3] == 'm' && !data[i + 4])
		{
			valid = 1;
			break ;
		}
		i++;
	}
	return (valid);
}
