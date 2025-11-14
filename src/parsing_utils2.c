/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:56:13 by plerick           #+#    #+#             */
/*   Updated: 2025/11/14 14:57:35 by adrien           ###   ########.fr       */
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

int	check_empty_lines_in_map(char *content)
{
	int		i;
	int		j;
	int		map_started;

	map_started = 0;
	i = 0;
	while (content[i])
	{
		if ((content[i] == '1' || content[i] == '0')
			&& (i == 0 || content[i - 1] == '\n'))
			map_started = 1;
		if (map_started && content[i] == '\n' && content[i + 1] == '\n')
		{
			j = i + 2;
			while (content[j] && (content[j] == ' ' || content[j] == '\t'))
				j++;
			if (content[j] && content[j] != '\n')
				return (write(2, "Empty line in map\n", 18), 0);
		}
		i++;
	}
	return (1);
}
