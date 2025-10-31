/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:44:07 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 14:22:25 by abidaux          ###   ########.fr       */
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
	if (keycode == 65307) // ESC
		close_window(data);
	else if (keycode == 119) // W
		move_forward(data);
	else if (keycode == 115) // S
		move_backward(data);
	else if (keycode == 65361) // Left arrow
		rotate_left(data);
	else if (keycode == 65363) // Right arrow
		rotate_right(data);

	return (0);
}
