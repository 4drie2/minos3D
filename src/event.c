/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:44:07 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 14:12:33 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** key_press : gère les touches du clavier
**
** MacOS keycodes :
** 53 = ESC
** 13 = W (avancer)
** 1 = S (reculer)
** 123 = Flèche gauche (tourner)
** 124 = Flèche droite (tourner)
*/
int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		close_window(data);
	else if (keycode == 13)
		move_forward(data);
	else if (keycode == 1)
		move_backward(data);
	else if (keycode == 123)
		rotate_left(data);
	else if (keycode == 124)
		rotate_right(data);

	return (0);
}
