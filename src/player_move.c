/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:00:00 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/11 04:31:45 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_data *data)
{
	double	move_speed;
	double	move_x;
	double	move_y;

	move_speed = 0.05;
	move_x = data->player.dir_x * move_speed;
	move_y = data->player.dir_y * move_speed;
	move_player(data, move_x, move_y);
}

void	move_backward(t_data *data)
{
	double	move_speed;
	double	move_x;
	double	move_y;

	move_speed = 0.05;
	move_x = -data->player.dir_x * move_speed;
	move_y = -data->player.dir_y * move_speed;
	move_player(data, move_x, move_y);
}

void	move_right(t_data *data)
{
	double	move_speed;
	double	move_x;
	double	move_y;

	move_speed = 0.05;
	move_x = data->player.dir_y * move_speed;
	move_y = -data->player.dir_x * move_speed;
	move_player(data, move_x, move_y);
}

void	move_left(t_data *data)
{
	double	move_speed;
	double	move_x;
	double	move_y;

	move_speed = 0.05;
	move_x = -data->player.dir_y * move_speed;
	move_y = data->player.dir_x * move_speed;
	move_player(data, move_x, move_y);
}

void	rotate_left(t_data *data)
{
	double	rot_speed;

	rot_speed = 0.05;
	rotate_player(&data->player, rot_speed);
}

void	rotate_right(t_data *data)
{
	double	rot_speed;

	rot_speed = 0.05;
	rotate_player(&data->player, -rot_speed);
}
