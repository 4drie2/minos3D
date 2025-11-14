/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:13:12 by plerick           #+#    #+#             */
/*   Updated: 2025/11/14 15:00:05 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	is_map_start(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '0'
			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return (0);
		line++;
	}
	return (1);
}

int	validate_map_chars(char **lines, int start, int height)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < height)
	{
		if (!lines[start + y] || lines[start + y][0] == '\0')
			return (write(2, "Empty line in map\n", 18), 0);
		x = 0;
		while (lines[start + y][x])
		{
			c = lines[start + y][x];
			if (!is_valid_map_char(c))
			{
				write(2, "Invalid character in map: '", 27);
				write(2, &c, 1);
				write(2, "'\n", 2);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
