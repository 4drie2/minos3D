/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:22:36 by plerick           #+#    #+#             */
/*   Updated: 2025/11/18 19:14:24 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_heightandwithd(char **lines, int start, t_data *data)
{
	int		height;
	int		width;
	int		y;
	size_t	len;

	height = 0;
	width = 0;
	y = start;
	while (lines[y])
	{
		len = ft_strlen(lines[y]);
		if (len == 0 && lines[y + 1])
		{
			write(2, "Empty line in map\n", 18);
			ft_error("Invalid map structure", data);
		}
		if (len > (size_t)width)
			width = len;
		height++;
		y++;
	}
	data->config.map_height = height;
	data->config.map_width = width;
}

char	**duplicate_map(char **map, int height, int start)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < height)
	{
		copy[y] = ft_strdup(map[y + start]);
		y++;
	}
	copy[height] = NULL;
	return (copy);
}

void	flood_fill(char **map, int x, int y, int *ret)
{
	if (y < 0 || (size_t)x > ft_strlen(map[y]) || x < 0
		|| map[y][x] == '\n' || map[y][x] == '\0' || map[y][x] == ' ')
	{
		(*ret)++;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x, y - 1, ret);
	flood_fill(map, x, y + 1, ret);
	flood_fill(map, x - 1, y, ret);
	flood_fill(map, x + 1, y, ret);
}
