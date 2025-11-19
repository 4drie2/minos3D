/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:44:07 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:56:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** mouse_move: handles mouse movement for rotation
** Calculates the delta between the current position and the last position
*/
int	mouse_move(int x, int y, t_data *data)
{
	int	center_x;
	int	delta_x;

	(void)y;
	if (MOUSE_SENSITIVITY <= 0)
		return (0);
	center_x = WIN_WIDTH / 2;
	if (data->mouse.first_move)
	{
		data->mouse.first_move = 0;
		mlx_mouse_move(data->mlx, data->win, center_x, WIN_HEIGHT / 2);
		return (0);
	}
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	rotate_player(&data->player, delta_x * MOUSE_SENSITIVITY);
	mlx_mouse_move(data->mlx, data->win, center_x, WIN_HEIGHT / 2);
	return (0);
}

/*
** key_press: registers the pressed keys
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
** key_release: registers the released keys
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
** update_movement: handles movements based on pressed keys
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
