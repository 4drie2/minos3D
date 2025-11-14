/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:22:33 by plerick           #+#    #+#             */
/*   Updated: 2025/11/14 14:09:00 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_map_closed(t_data *data, char **lines, int start)
{
	char	**copy;
	int		ret;

	ret = 0;
	copy = duplicate_map(lines, data->config.map_height, start);
	if (copy == NULL)
		return (write(2, "bad copy of map\n", 16), 0);
	flood_fill(copy, (int)data->player.pos_x, (int)data->player.pos_y, &ret);
	ft_free_array(copy);
	if (ret != 0)
		return (write(2, "map not good with flood_fill\n", 29), 0);
	return (1);
}

void	find_player(t_data *data, int x, int y, char **lines)
{
	char	c;

	c = lines[y][x];
	if (!(c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return ;
	if (lines[y - 1][x] == '1' && lines[y + 1][x] == '1'
		&& lines[y][x - 1] == '1' && lines[y][x + 1] == '1')
		return ((void)write(2, "Player spawns inside walls\n", 27));
	if (c == 'N')
		char_play_n(data);
	else if (c == 'S')
		char_play_s(data);
	else if (c == 'E')
		char_play_e(data);
	else if (c == 'W')
		char_play_w(data);
	data->player.pos_x = x;
	lines[y][x] = '0';
	data->config.player_count++;
}

static int	char_to_int(char c)
{
	if (c == '1')
		return (1);
	if (c == '0' || c == ' ')
		return (0);
	return (0);
}

static void	map_to_int(t_data *data, char **lines, int start)
{
	int	y;
	int	x;
	int	len;

	data->map = malloc(sizeof(int *) * data->config.map_height);
	if (!data->map)
		ft_error("Malloc failed for map_int", data);
	y = 0;
	while (y < data->config.map_height)
	{
		data->map[y] = malloc(sizeof(int) * data->config.map_width);
		if (!data->map[y])
			ft_error("Malloc failed for map_int[y]", data);
		len = ft_strlen(lines[start + y]);
		x = -1;
		while (++x < data->config.map_width)
		{
			if (x < len)
				data->map[y][x] = char_to_int(lines[start + y][x]);
			else
				data->map[y][x] = 0;
		}
		y++;
	}
	data->chec_map_used = 1;
}

int	parse_map(char **lines, int start, t_data *data)
{
	int	y;
	int	x;

	set_heightandwithd(lines, start, data);
	y = 0;
	while (y < data->config.map_height)
	{
		x = 0;
		while (x < data->config.map_width && lines[y + start][x])
		{
			find_player(data, x, start + y, lines);
			if (data->player.pos_x != -1 && data->player.pos_y == -1)
				data->player.pos_y = y;
			x++;
		}
		y++;
	}
	if (data->config.player_count != 1)
		return (write(2, "Invalid player count\n", 21), 0);
	if (!validate_map_closed(data, lines, start))
		return (write(2, "Invalid map\n", 12), 0);
	map_to_int(data, lines, start);
	return (1);
}
