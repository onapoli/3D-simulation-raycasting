/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 14:13:29 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/16 12:08:10 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	go_forward(t_session *session, double angle)
{
	double	new_pos[2];
	int		x_interpret;
	int		y_interpret;
	size_t	cell_pos[2];

	new_pos[0] = session->player.x_pos + cos(angle) * 5;
	new_pos[1] = session->player.y_pos + sin(angle) * 5;
	if (get_direction(angle, 'x'))
		x_interpret = ceil(new_pos[0]);
	else
		x_interpret = new_pos[0];
	if (get_direction(angle, 'y'))
		y_interpret = ceil(new_pos[1]);
	else
		y_interpret = new_pos[1];
	get_cell(cell_pos, x_interpret, y_interpret, session->level.cell_length);
	if (check_wall(session->level.map, cell_pos[0], cell_pos[1]))
		return (0);
	session->player.x_pos = new_pos[0];
	session->player.y_pos = new_pos[1];
	return (0);
}

static int	go_left(t_session *session, double angle)
{
	angle = normalize_angle(angle - deg_2_rad(90));
	go_forward(session, angle);
	return (0);
}

static int	go_backwards(t_session *session, double angle)
{
	double	new_pos[2];
	int		x_interpret;
	int		y_interpret;
	size_t	cell_pos[2];

	new_pos[0] = session->player.x_pos - cos(angle) * 5;
	new_pos[1] = session->player.y_pos - sin(angle) * 5;
	if (!get_direction(angle, 'x'))
		x_interpret = ceil(new_pos[0]);
	else
		x_interpret = new_pos[0];
	if (!get_direction(angle, 'y'))
		y_interpret = ceil(new_pos[1]);
	else
		y_interpret = new_pos[1];
	get_cell(cell_pos, x_interpret, y_interpret, session->level.cell_length);
	if (check_wall(session->level.map, cell_pos[0], cell_pos[1]))
		return (0);
	session->player.x_pos = new_pos[0];
	session->player.y_pos = new_pos[1];
	return (0);
}

static int	go_right(t_session *session, double angle)
{
	angle = normalize_angle(angle + deg_2_rad(90));
	go_forward(session, angle);
	return (0);
}

int			move(t_session *session, int keycode)
{
	if (keycode == 119)
		go_forward(session, session->player.angle);
	if (keycode == 97)
		go_left(session, session->player.angle);
	if (keycode == 115)
		go_backwards(session, session->player.angle);
	if (keycode == 100)
		go_right(session, session->player.angle);
	return (0);
}
