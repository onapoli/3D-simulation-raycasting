/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function_utilities_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:15:30 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/08 12:48:03 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_session *session)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(session->textures[i].path);
		mlx_destroy_image(session->mlx, session->textures[i].texture);
		i++;
	}
	free(session->sprite_texture.path);
	mlx_destroy_image(session->mlx, session->sprite_texture.texture);
}

int		start_raycasting(t_session *session, double *z_buffer)
{
	if (raycaster(session, z_buffer) == -1)
	{
		write(1, "raycasting failed.", 18);
		return (-1);
	}
	if (project_sprites(session, z_buffer) == -1)
	{
		write(1, "drawing sprites failed.", 23);
		return (-1);
	}
	return (0);
}

void	ft_adjust_window_size(t_session *session)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(session->mlx, &screen_width, &screen_height);
	if (session->win_width > screen_width)
		session->win_width = screen_width;
	if (session->win_height > screen_height)
		session->win_height = screen_height;
}

void	handle_window_creation(int argc, char **argv, t_session *session)
{
	if (argc > 2)
	{
		if (argc > 3)
		{
			write(1, "Error\nToo many arguments when executing program.\n",
			sizeof("Error\nToo many arguments when executing program.\n"));
			exit(EXIT_FAILURE);
		}
		if (!ft_strcmp(argv[2], "--save"))
		{
			write(1, "Error\nBad arguments.\n", 21);
			exit(EXIT_FAILURE);
		}
	}
	else
		session->window = mlx_new_window(session->mlx, session->win_width,
		session->win_height, "cub3D Window");
}

void	create_session_image(t_session *session)
{
	session->image = mlx_new_image(session->mlx,
	session->win_width, session->win_height);
	session->image_data = mlx_get_data_addr(session->image,
	&(session)->image_bpp, &(session)->image_size_line,
	&(session)->image_endian);
}
