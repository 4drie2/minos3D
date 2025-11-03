/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 18:55:55 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	all_elements_set(t_config *config)
{
	if (!config->no_texture || !config->so_texture || !config->we_texture
		|| !config->ea_texture || config->floor.r == -1
		|| config->ceiling.r == -1)
		return (0);
	return (1);
}

static void	process_lines(char **split_content, t_config *config)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (split_content[i])
	{
		trimmed = ft_strtrim(split_content[i], " \t");
		if (ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			i++;
			continue;
		}
		if (is_map_start(trimmed))
		{
			free(trimmed);
			break;
		}
		parse_line(trimmed, config);
		free(trimmed);
		i++;
	}
	if (!all_element_set(config))
		ft_error("Missing config elem");
	parse_map(split_content, i, config);
}

static int	check_extension(char *filename)
{
	char	*dot;
	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".cub") != 0)
		return (0);
	return (1);
}

static char *read_file(char *filename)
{
	int		fd;
	char	*line;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	while ((line = get_next_line(fd)))
	{
		content = ft_strjoin_free(content, line);
		free(line);
	}
	close(fd);
	return (content);
}

int	parse_file(t_data *data, char *filename)
{
	char	*content;
	char	**split_content;

	content = NULL;
	split_content = NULL;
	if (!check_extension(char *filename))
		return (write(2, "error, bad extension\n", 22), 0);
	if ((content = read_file(char *filename)) == NULL)
		return (write(2, "error, bad read\n", 17), 0);
	split_content = ft_split(content, '\n');
	ft_printf("%s", content); //test
	free(content);
	process_lines(split_content, data->config);
	return (1);
}
