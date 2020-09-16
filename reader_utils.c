/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 12:42:59 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 14:25:18 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

size_t	ft_strlen(char const *input)
{
	size_t	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	if (!(dest = malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int		send_to_process_data(char *line, t_session *session)
{
	if (process_data(line, session) == -1)
	{
		free(line);
		write(1, "Error\nBad data in .cub file.\n", 29);
		return (-1);
	}
	return (0);
}

int		ft_open_file(int *fd, char *file_path)
{
	if (!ft_strcmp(&file_path[ft_strlen(file_path) - 4], ".cub"))
	{
		write(1, "Error\nInvalid file type.\n", 25);
		return (-1);
	}
	if ((*fd = open(file_path, O_RDONLY)) == -1)
	{
		perror("Error\nCan't open file.");
		return (-1);
	}
	return (0);
}
