/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:56:13 by plerick           #+#    #+#             */
/*   Updated: 2025/11/18 19:14:24 by abidaux          ###   ########.fr       */
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
				return (write(2, "Empty line in map\n", 18), 0);
		}
		i++;
	}
	return (1);
}

static int	skip_to_map_start(char *content, int start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[j] && i < start)
	{
		while (content[j] == '\n')
			j++;
		while (content[j] && content[j] != '\n')
			j++;
		if (content[j] == '\n')
			j++;
		i++;
	}
	while (content[j] == '\n')
		j++;
	return (j);
}

static int	validate_map_line(char **lines, char *content, int i, int j)
{
	int	k;

	if (content[j] == '\n')
		return (0);
	k = 0;
	while (content[j + k] && content[j + k] != '\n')
		k++;
	if (ft_strncmp(lines[i], content + j, k - 1) != 0
		|| lines[i][k] != '\0')
		return (0);
	return (1);
}

int	check_empty_lines_in_map(char **lines, int start, t_data *data)
{
	char	*content;
	int		i;
	int		j;
	int		k;

	content = data->content;
	j = skip_to_map_start(content, start);
	i = start;
	while (lines[i])
	{
		if (!validate_map_line(lines, content, i, j))
			return (0);
		k = 0;
		while (content[j + k] && content[j + k] != '\n')
			k++;
		j += k;
		if (content[j] == '\n')
			j++;
		i++;
	}
	return (1);
}
