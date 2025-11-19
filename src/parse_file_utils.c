/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:43:23 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:52:34 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".cub") != 0)
		return (0);
	return (1);
}

char	*read_file(char *filename)
{
	int		fd;
	char	*line;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		content = ft_strjoin_free(content, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}
