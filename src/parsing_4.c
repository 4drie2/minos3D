/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:22:36 by plerick           #+#    #+#             */
/*   Updated: 2025/11/11 20:22:36 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

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

