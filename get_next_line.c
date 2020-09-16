/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 13:36:25 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/02 11:10:10 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *s)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] != '\n')
		return (0);
	if (!(line = malloc(sizeof(char) * (i + 1))))
		return (0);
	line[i] = 0;
	j = 0;
	while (j < i)
	{
		line[j] = s[j];
		j++;
	}
	return (line);
}

static char	*ft_get_after_line(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (&s[++i]);
}

static void	ft_save_buffer(char **s_memory, char *buffer, int fd)
{
	char	*aux;

	aux = ft_strjoin(s_memory[fd], buffer);
	free(s_memory[fd]);
	s_memory[fd] = ft_strdup(aux);
	free(aux);
}

static int	ft_line_result(char **s_memory, char **line, int fd)
{
	char	*aux;

	if (ft_check_nl(s_memory[fd]))
	{
		if (*line)
			free(*line);
		*line = ft_get_line(s_memory[fd]);
		aux = ft_strdup(ft_get_after_line(s_memory[fd]));
		free(s_memory[fd]);
		s_memory[fd] = ft_strdup(aux);
		free(aux);
		return (1);
	}
	if (*line)
		free(*line);
	*line = ft_strdup(s_memory[fd]);
	free(s_memory[fd]);
	s_memory[fd] = 0;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*s_memory[4096];
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!s_memory[fd])
		s_memory[fd] = ft_strdup("");
	else if (ft_check_nl(s_memory[fd]))
		return (ft_line_result(s_memory, line, fd));
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		if ((bytes_read = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (-1);
		buffer[bytes_read] = 0;
		ft_save_buffer(s_memory, buffer, fd);
		if (ft_check_nl(s_memory[fd]))
			break ;
	}
	free(buffer);
	return (ft_line_result(s_memory, line, fd));
}
