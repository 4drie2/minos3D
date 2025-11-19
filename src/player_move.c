/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:09:24 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:53:19 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.dir_x * data->move_speed;
	move_y = data->player.dir_y * data->move_speed;
	move_player(data, move_x, move_y);
}

void	move_backward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = -data->player.dir_x * data->move_speed;
	move_y = -data->player.dir_y * data->move_speed;
	move_player(data, move_x, move_y);
}

void	move_right(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = -data->player.dir_y * (0.5 * data->move_speed);
	move_y = data->player.dir_x * (0.5 * data->move_speed);
	move_player(data, move_x, move_y);
}

void	move_left(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.dir_y * (0.5 * data->move_speed);
	move_y = -data->player.dir_x * (0.5 * data->move_speed);
	move_player(data, move_x, move_y);
}
