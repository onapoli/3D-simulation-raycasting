/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:18:24 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/03 13:13:47 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotate(t_session *session, int keycode)
{
	if (keycode == 65363)
		session->player.angle = normalize_angle(session->player.angle +
		deg_2_rad(10));
	if (keycode == 65361)
		session->player.angle = normalize_angle(session->player.angle -
		deg_2_rad(10));
	return (0);
}
