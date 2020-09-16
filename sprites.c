/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:41:16 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:41:48 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	update_sprite_info(t_sprite *sprites, t_player player,
double fov)
{
	size_t	count;

	count = 0;
	while (sprites)
	{
		sprites->data.angle = get_sprite_angle(sprites->data.x_pos,
		sprites->data.y_pos, player.x_pos, player.y_pos);
		sprites->data.show = get_sprite_visibility(sprites->data.angle,
		player.angle, fov);
		if (sprites->data.show)
		{
			sprites->data.distance = get_2_point_distance(sprites->data.x_pos,
			sprites->data.y_pos, player.x_pos, player.y_pos);
			count++;
		}
		sprites = sprites->next;
	}
	return (count);
}

static int		get_visible_sprites(t_sprite_data *visible_sprites,
t_sprite *sprites)
{
	size_t i;

	i = 0;
	while (sprites)
	{
		if (sprites->data.show)
		{
			visible_sprites[i] = sprites->data;
			i++;
		}
		sprites = sprites->next;
	}
	return (0);
}

static int		sort_sprites_desc_dist(t_sprite_data *sprites, size_t size)
{
	t_sprite_data	aux;
	size_t			i;
	size_t			j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (sprites[j].distance < sprites[i].distance)
			{
				aux = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = aux;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int				project_sprites(t_session *session, double *z_buffer)
{
	size_t			v_sprites_size;
	t_sprite_data	*visible_sprites;

	v_sprites_size = update_sprite_info(session->level.sprites,
	session->player, session->fov);
	if (!v_sprites_size)
		return (0);
	if (!(visible_sprites =
	malloc(sizeof(t_sprite_data) * (v_sprites_size + 1))))
		return (-1);
	visible_sprites[v_sprites_size].x_pos = -1;
	get_visible_sprites(visible_sprites, session->level.sprites);
	sort_sprites_desc_dist(visible_sprites, v_sprites_size);
	draw_sprites(visible_sprites, session, z_buffer);
	free(visible_sprites);
	return (0);
}
