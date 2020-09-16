/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 16:10:12 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/09 16:15:24 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		timer(void *param)
{
	t_session *session;

	session = param;
	if (session->time < 100)
		session->time += 0.000001;
	return (0);
}

void	time_update(int keycode, t_session *session)
{
	session->lastkey = keycode;
	session->time = 0;
}
