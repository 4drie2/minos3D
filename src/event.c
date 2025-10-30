/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:44:07 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/30 20:45:31 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** key_press : gère les touches du clavier
** ESC (53) : ferme le programme
** W/S (13/1) : avance/recule
** A/D (0/2) : gauche/droite (strafe)
** LEFT/RIGHT (123/124) : rotation
*/
int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		close_window(data);
	(void)data;
	return (0);
}
