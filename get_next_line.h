/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 13:58:08 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/03 13:02:07 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 32

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *src);
int		ft_check_nl(char *s);
int		get_next_line(int fd, char **line);

#endif
