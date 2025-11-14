/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:56:13 by plerick           #+#    #+#             */
/*   Updated: 2025/11/14 12:59:45 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	char_play_n(t_data *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
}

void	char_play_s(t_data *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = 1.0;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.0;
}

void	char_play_e(t_data *data)
{
	data->player.dir_x = 1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = 0.66;
}

void	char_play_w(t_data *data)
{
	data->player.dir_x = -1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = -0.66;
}
