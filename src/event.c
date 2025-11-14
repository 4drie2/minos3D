/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:44:07 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/14 07:32:57 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** mouse_move : gère le mouvement de la souris pour rotation
** Calcule le delta entre la position actuelle et la dernière position
*/
int	mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	rot_angle;

	(void)y;
	if (data->mouse.first_move)
	{
		data->mouse.last_x = x;
		data->mouse.last_y = y;
		data->mouse.first_move = 0;
		return (0);
	}
	delta_x = x - data->mouse.last_x;
	if (delta_x != 0)
	{
		rot_angle = delta_x * MOUSE_SENSITIVITY;
		rotate_player(&data->player, rot_angle);
	}
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	return (0);
}

/*
** key_press : enregistre les touches pressées
*/
int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_w)
		data->keys.w = 1;
	else if (keycode == XK_s)
		data->keys.s = 1;
	else if (keycode == XK_a)
		data->keys.a = 1;
	else if (keycode == XK_d)
		data->keys.d = 1;
	else if (keycode == XK_Left)
		data->keys.left = 1;
	else if (keycode == XK_Right)
		data->keys.right = 1;
	else if (keycode == XK_Shift_L)
		data->keys.shift = 1;
	return (0);
}

/*
** key_release : enregistre les touches relâchées
*/
int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.w = 0;
	else if (keycode == XK_s)
		data->keys.s = 0;
	else if (keycode == XK_a)
		data->keys.a = 0;
	else if (keycode == XK_d)
		data->keys.d = 0;
	else if (keycode == XK_Left)
		data->keys.left = 0;
	else if (keycode == XK_Right)
		data->keys.right = 0;
	else if (keycode == XK_Shift_L)
		data->keys.shift = 0;
	return (0);
}

/*
** update_movement : gère les mouvements en fonction des touches pressées
*/
void	update_movement(t_data *data)
{
	if (data->keys.shift)
		data->move_speed = MOVE_SPEED * 2;
	else
		data->move_speed = MOVE_SPEED;
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(data);
	if (data->keys.right)
		rotate_right(data);
}
