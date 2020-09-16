/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:22:35 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/15 13:35:24 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	j_loop(t_session *session, t_sprite_draw *sprite_draw)
{
	while (sprite_draw->j < sprite_draw->j_finish)
	{
		get_texture(session->sprite_texture,
		(int)floor(sprite_draw->i_tex), (int)floor(sprite_draw->j_tex),
		sprite_draw->texture);
		if (!(sprite_draw->texture[0] == 0 &&
		sprite_draw->texture[1] == 0 && sprite_draw->texture[2] == 0 &&
		sprite_draw->texture[3] == 0))
			draw_texture(session, sprite_draw->i, sprite_draw->j,
			sprite_draw->texture);
		sprite_draw->j_tex += sprite_draw->height_texture_increment;
		(sprite_draw->j) += 1;
	}
}

static void	case_xinit_negative(t_session *session, t_sprite_view *sprite_view,
t_sprite_draw *sprite_draw)
{
	sprite_draw->i = 0;
	sprite_draw->i_tex = ((double)(0 - sprite_draw->x_init) /
	(double)sprite_view->pixel_width) *
	(double)session->sprite_texture.tex_width;
}

static void	calculate_iterators(t_session *session, t_sprite_view *sprite_view,
t_sprite_draw *sprite_draw)
{
	sprite_draw->x_init = sprite_view->x_midpoint -
	(int)floor(sprite_view->pixel_width / 2);
	sprite_draw->x_finish = sprite_view->x_midpoint +
	(int)floor(sprite_view->pixel_width / 2);
	sprite_draw->width_texture_increment =
	(double)session->sprite_texture.tex_width /
	(double)sprite_view->pixel_width;
	sprite_draw->height_texture_increment =
	(double)session->sprite_texture.tex_height /
	(double)sprite_view->pixel_height;
	sprite_draw->final_height = sprite_view->pixel_height;
	if (sprite_view->pixel_height > session->win_height)
		sprite_draw->final_height = session->win_height;
	sprite_draw->i = sprite_draw->x_init;
	sprite_draw->i_tex = 0;
	if (sprite_draw->x_init < 0)
		case_xinit_negative(session, sprite_view, sprite_draw);
	sprite_draw->j_start = (int)floor(session->win_height / 2 -
	sprite_draw->final_height / 2);
	sprite_draw->j_finish = sprite_draw->j_start + sprite_draw->final_height;
	sprite_draw->j_tex_start = ((sprite_view->pixel_height -
	sprite_draw->final_height) / 2) * sprite_draw->height_texture_increment;
}

int			draw_single_sprite(t_session *session, t_sprite_view *sprite_view,
double distance, double *z_buffer)
{
	t_sprite_draw	*sprite_draw;

	if (!(sprite_draw = malloc(sizeof(t_sprite_draw))))
		return (-1);
	calculate_iterators(session, sprite_view, sprite_draw);
	while (sprite_draw->i < sprite_draw->x_finish &&
	sprite_draw->i < session->win_width)
	{
		if (z_buffer[sprite_draw->i] > distance)
		{
			sprite_draw->j = sprite_draw->j_start;
			sprite_draw->j_tex = sprite_draw->j_tex_start;
			j_loop(session, sprite_draw);
		}
		sprite_draw->i_tex += sprite_draw->width_texture_increment;
		(sprite_draw->i) += 1;
	}
	free(sprite_draw);
	return (0);
}
