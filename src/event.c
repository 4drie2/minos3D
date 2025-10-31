/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:44:07 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 14:37:24 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** key_press : gère les touches du clavier
**
** Linux keycodes (X11) :
** 65307 = ESC
** 119 = W (avancer)
** 115 = S (reculer)
** 65361 = Flèche gauche (tourner)
** 65363 = Flèche droite (tourner)
*/
int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_W)
		move_forward(data);
	else if (keycode == XK_S)
		move_backward(data);
	else if (keycode == XK_A)
		move_left(data);
	else if (keycode == XK_D)
		move_right(data);
	else if (keycode == XK_Left)
		rotate_left(data);
	else if (keycode == XK_Right)
		rotate_right(data);

	return (0);
}
