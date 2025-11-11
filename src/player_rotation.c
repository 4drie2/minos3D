/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:08:34 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/11 04:31:44 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handle_rotation(t_data *data)
{
	double	rot_speed;

	rot_speed = 0.05;
	if (data->keys.left)
		rotate_player(&data->player, rot_speed);
	if (data->keys.right)
		rotate_player(&data->player, -rot_speed);
}

void	handle_movement(t_data *data)
{
	double	move_speed;
	double	move_x;
	double	move_y;

	move_speed = 0.05;
	if (data->keys.w)
	{
		move_x = data->player.dir_x * move_speed;
		move_y = data->player.dir_y * move_speed;
		move_player(data, move_x, move_y);
	}
	if (data->keys.s)
	{
		move_x = -data->player.dir_x * move_speed;
		move_y = -data->player.dir_y * move_speed;
		move_player(data, move_x, move_y);
	}
	handle_strafe_movement(data, move_speed);
}

void	handle_strafe_movement(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	if (data->keys.a)
	{
		move_x = data->player.dir_y * move_speed;
		move_y = -data->player.dir_x * move_speed;
		move_player(data, move_x, move_y);
	}
	if (data->keys.d)
	{
		move_x = -data->player.dir_y * move_speed;
		move_y = data->player.dir_x * move_speed;
		move_player(data, move_x, move_y);
	}
}
