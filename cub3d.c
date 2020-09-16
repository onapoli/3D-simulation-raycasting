/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 18:13:30 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/13 13:06:44 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "reader.h"

static int	load_textures(t_session *session)
{
	if (load_wall_textures(session) == -1)
		return (-1);
	session->sprite_texture.texture = mlx_xpm_file_to_image(session->mlx,
	session->sprite_texture.path, &session->sprite_texture.tex_width,
	&session->sprite_texture.tex_height);
	if (!session->sprite_texture.texture)
	{
		write(1, "Error\nBad texture file name/s.\n", 31);
		return (-1);
	}
	session->sprite_texture.texture_data =
	mlx_get_data_addr(session->sprite_texture.texture,
	&session->sprite_texture.tex_bpp, &session->sprite_texture.tex_size_line,
	&session->sprite_texture.tex_endian);
	return (0);
}

static int	update_view(t_session *session)
{
	double	z_buffer[session->win_width];

	if (start_raycasting(session, z_buffer) == -1)
		return (-1);
	if (session->window)
		mlx_put_image_to_window(session->mlx, session->window,
		session->image, 0, 0);
	else
	{
		if (create_bmp(session->win_width, session->win_height,
		session->image_bpp, session->image_data) == -1)
		{
			write(1, "bmp file creation failed.", 25);
			return (-1);
		}
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static int	key_press(int keycode, void *param)
{
	t_session *session;

	session = param;
	if ((!session->lastkey || session->lastkey != keycode) ||
	(session->lastkey == keycode && session->time > 0.1))
	{
		if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
			move(session, keycode);
		if (keycode == 65361 || keycode == 65363)
			rotate(session, keycode);
		if (keycode == 65307)
		{
			free_textures(session);
			mlx_destroy_image(session->mlx, session->image);
			mlx_destroy_window(session->mlx, session->window);
			free_map(session->level.map);
			free_sprites(&(session)->level.sprites);
			free(session);
			exit(EXIT_SUCCESS);
		}
		if (update_view(session) == -1)
			exit(EXIT_FAILURE);
		time_update(keycode, session);
	}
	return (0);
}

static int	exit_program(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int			main(int argc, char **argv)
{
	t_session	*session;

	if (!(session = malloc(sizeof(t_session))))
		return (-1);
	set_default_level_values(session);
	check_minimum_args(argc);
	if (ft_read_file(session, argv[1]) == -1)
		exit(EXIT_FAILURE);
	session->mlx = mlx_init();
	ft_adjust_window_size(session);
	session->projection_distance =
	(session->win_width / 2) / tan(session->fov / 2);
	handle_window_creation(argc, argv, session);
	create_session_image(session);
	if (load_textures(session) == -1)
		exit(EXIT_FAILURE);
	if (update_view(session) == -1)
		exit(EXIT_FAILURE);
	if (session->window)
	{
		mlx_hook(session->window, 2, 1L << 0, key_press, session);
		mlx_hook(session->window, 17, 1L << 17, exit_program, session);
		launch_hooks_n_loops(session);
	}
	return (0);
}
