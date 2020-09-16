/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 12:20:18 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 13:05:54 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_pixel(t_session *session, int x, int y, unsigned long color)
{
	int pixel;

	pixel = (y * session->image_size_line) + (x * 4);
	if (session->image_endian == 1)
	{
		session->image_data[pixel + 1] = (color >> 16) & 0xFF;
		session->image_data[pixel + 2] = (color >> 8) & 0xFF;
		session->image_data[pixel + 3] = color & 0xFF;
	}
	else if (session->image_endian == 0)
	{
		session->image_data[pixel + 0] = color & 0xFF;
		session->image_data[pixel + 1] = (color >> 8) & 0xFF;
		session->image_data[pixel + 2] = (color >> 16) & 0xFF;
	}
	return (0);
}

int	draw_texture(t_session *session, int x, int y, char texture[4])
{
	int pixel;

	pixel = (y * session->image_size_line) + (x * 4);
	if (session->image_endian == 1)
	{
		session->image_data[pixel + 0] = texture[0];
		session->image_data[pixel + 1] = texture[1];
		session->image_data[pixel + 2] = texture[2];
		session->image_data[pixel + 3] = texture[3];
	}
	else if (session->image_endian == 0)
	{
		session->image_data[pixel + 0] = texture[0];
		session->image_data[pixel + 1] = texture[1];
		session->image_data[pixel + 2] = texture[2];
		session->image_data[pixel + 3] = texture[3];
	}
	return (0);
}

int	get_texture(t_texture texture_src, int x, int y, char texture[4])
{
	int pixel;

	pixel = (y * texture_src.tex_size_line) + (x * 4);
	if (texture_src.tex_endian == 1)
	{
		texture[0] = texture_src.texture_data[pixel + 0];
		texture[1] = texture_src.texture_data[pixel + 1];
		texture[2] = texture_src.texture_data[pixel + 2];
		texture[3] = texture_src.texture_data[pixel + 3];
	}
	else if (texture_src.tex_endian == 0)
	{
		texture[0] = texture_src.texture_data[pixel + 0];
		texture[1] = texture_src.texture_data[pixel + 1];
		texture[2] = texture_src.texture_data[pixel + 2];
		texture[3] = texture_src.texture_data[pixel + 3];
	}
	return (0);
}
