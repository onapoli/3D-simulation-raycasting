/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:10:01 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 12:23:25 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "cub3d.h"

typedef struct	s_map_line
{
	char				*line;
	struct s_map_line	*next;
}				t_map_line;

size_t			ft_strlen(char const *input);
char			*ft_strdup(char *src);
int				send_to_process_data(char *line, t_session *session);
int				ft_open_file(int *fd, char *file_path);
int				validate_line_nospace(size_t column, char element,
int *first_num, size_t this_line_limits[2]);
int				validate_line_zeroes(char **map, size_t row, size_t column,
size_t prev_line_limits[2]);
int				validate_last_line(char **map, size_t row);
int				validate_first_line(char **map, size_t row,
size_t line_limits[2]);
int				validate_map(t_session *session);
int				generate_map(char ***map, t_map_line *map_lines);
int				add_map_line(char *map_line, t_map_line **map_lines);
int				mini_atoi(char *data, int *i, char delimiter);
int				unify_rgb(unsigned long *color, int rgb[3]);
int				get_rgb(char *data, int *i, int *rgb);
int				validate_path(char *data);
int				add_data(int data_type, char *data, t_session *session);
int				process_data(char *line, t_session *session);
int				ft_read_file(t_session *session, char *file_path);

#endif
