/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:56:13 by plerick           #+#    #+#             */
/*   Updated: 2025/11/17 18:38:47 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	space_in_map(char *content, int i)
{
	int	j;
	
	while (content[i] != '\0')
	{
		if (content[i] == '\n' && content[i + 1] == '\n')
		{
			j = i + 2;
			while (content[j] && (content[j] == ' ' || content[j] == '\t'))
				j++;
			if (content[j] && content[j] != '\n')
			{
				printf("char : %c%c%c%c%c%c", content[j], content[j+1], content[j+2], content[j+3], content[j+4], content[j+5]);
				return (write(2, "Empty line in map\n", 18), 0);
			}
		}
		i++;
	}
	return (1);
}

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

int	check_empty_lines_in_map(char **lines, int start, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (data->content[j] && i < start)
	{
		while (data->content[j] == '\n')
			j++;
		while (data->content[j] && data->content[j] != '\n')
			j++;
		if (data->content[j] == '\n')
			j++;
		i++;
	}
	i = 0;
	while (lines[i])
	{
		if (data->content[j] == '\n')
			return (0);
		k = 0;
		while (data->content[j + k] && data->content[j + k] != '\n')
			k++;
		if (ft_strncmp(lines[i], data->content + j, k) != 0
			|| lines[i][k] != '\0')
			return (0);
		j += k;
		if (data->content[j] == '\n')
			j++;
		i++;
	}
	return (1);
}
