/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:19:49 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 13:00:32 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_ceil_floor(t_session *session, int x, int y_start,
int y_finish)
{
	int i;

	i = 0;
	while (i < y_start)
		draw_pixel(session, x, i++, session->level.ceiling_color);
	i = y_finish;
	while (i < session->win_height)
		draw_pixel(session, x, i++, session->level.floor_color);
	return (0);
}

static void	wall_draw_loop(t_session *session, int x, t_wall_draw *wall_draw)
{
	while (wall_draw->j < wall_draw->final_j)
	{
		get_texture(wall_draw->texture_src, (int)floor(wall_draw->i_tex),
		(int)floor(wall_draw->j_tex), wall_draw->texture);
		draw_texture(session, x, wall_draw->j, wall_draw->texture);
		wall_draw->j_tex += wall_draw->texture_increment;
		(wall_draw->j) += 1;
	}
}

static void	select_wall_tex(t_session *session, t_ray *ray,
t_wall_draw *wall_draw)
{
	if (ray->wall_intersect == 1 && get_direction(ray->angle, 'x'))
		wall_draw->texture_src = session->textures[1];
	if (ray->wall_intersect == 1 && !get_direction(ray->angle, 'x'))
		wall_draw->texture_src = session->textures[3];
	if (ray->wall_intersect == 2 && get_direction(ray->angle, 'y'))
		wall_draw->texture_src = session->textures[2];
	if (ray->wall_intersect == 2 && !get_direction(ray->angle, 'y'))
		wall_draw->texture_src = session->textures[0];
}

int			draw_wall_texture(t_session *session, int x, t_ray *ray)
{
	t_wall_draw	*wall_draw;

	if (!(wall_draw = malloc(sizeof(t_wall_draw))))
		return (-1);
	select_wall_tex(session, ray, wall_draw);
	wall_draw->final_wall_pixels = ray->wall_pixels;
	if (wall_draw->final_wall_pixels > session->win_height)
		wall_draw->final_wall_pixels = session->win_height;
	wall_draw->texture_increment =
	(double)wall_draw->texture_src.tex_height / (double)ray->wall_pixels;
	wall_draw->i_tex = ray->wall_pos / session->level.cell_length;
	wall_draw->i_tex = (wall_draw->i_tex - floor(wall_draw->i_tex)) *
	wall_draw->texture_src.tex_width;
	wall_draw->start_j = (int)floor(session->win_height / 2 -
	wall_draw->final_wall_pixels / 2);
	wall_draw->j = wall_draw->start_j;
	wall_draw->j_tex = ((ray->wall_pixels -
	wall_draw->final_wall_pixels) / 2) * wall_draw->texture_increment;
	wall_draw->final_j = wall_draw->j + wall_draw->final_wall_pixels;
	wall_draw_loop(session, x, wall_draw);
	draw_ceil_floor(session, x, wall_draw->start_j, wall_draw->final_j);
	free(wall_draw);
	return (0);
}

int			draw_sprites(t_sprite_data *sprites, t_session *session,
double *z_buffer)
{
	t_sprite_view	*sprite_view;

	if (!(sprite_view = malloc(sizeof(t_sprite_view))))
		return (-1);
	while (sprites->x_pos != -1)
	{
		sprite_view->x_midpoint = sprite_screen_midpoint(session->player.angle,
		sprites->angle, session->fov, session->win_width);
		sprite_view->pixel_width = get_wall_pixels(session->level.cell_length,
		sprites->distance, session->projection_distance);
		sprite_view->pixel_height = get_wall_pixels(session->level.cell_length,
		sprites->distance, session->projection_distance);
		draw_single_sprite(session, sprite_view, sprites->distance, z_buffer);
		sprites++;
	}
	free(sprite_view);
	return (0);
}
