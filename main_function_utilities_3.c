/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function_utilities_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:34:15 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/10 18:29:26 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		minimize(void *param)
{
	t_session *session;

	session = param;
	if (!session->win_minimized)
		session->win_minimized = 1;
	return (0);
}

int		maximize(t_session *session)
{
	double		z_buffer[session->win_width];

	if (session->win_minimized)
	{
		if (start_raycasting(session, z_buffer) == -1)
			exit(EXIT_FAILURE);
		mlx_clear_window(session->mlx, session->window);
		mlx_put_image_to_window(session->mlx, session->window,
		session->image, 0, 0);
		session->win_minimized = 0;
	}
	return (0);
}

int		load_wall_textures(t_session *session)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		session->textures[i].texture = mlx_xpm_file_to_image(session->mlx,
		session->textures[i].path, &session->textures[i].tex_width,
		&session->textures[i].tex_height);
		if (!session->textures[i].texture)
		{
			write(1, "Error\nBad texture file name/s.\n", 31);
			return (-1);
		}
		session->textures[i].texture_data =
		mlx_get_data_addr(session->textures[i].texture,
		&session->textures[i].tex_bpp, &session->textures[i].tex_size_line,
		&session->textures[i].tex_endian);
		i++;
	}
	return (0);
}

void	launch_hooks_n_loops(t_session *session)
{
	mlx_hook(session->window, 9, 1L << 21, maximize, session);
	mlx_hook(session->window, 10, 1L << 21, minimize, session);
	mlx_loop_hook(session->mlx, timer, session);
	mlx_loop(session->mlx);
}
