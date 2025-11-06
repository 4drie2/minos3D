/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/04 19:35:18 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	all_elements_set(t_config *config)
{
	if (!config->no_text_path || !config->so_text_path || !config->we_text_path
		|| !config->ea_text_path || config->floor.r == -1
		|| config->sky.r == -1)
		return (0);
	return (1);
}

static void	process_lines(char **split_content, t_data *data)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (split_content[i])
	{
		ft_printf("before trimmed : %s\n", split_content[i]); //test
		trimmed = ft_strtrim(split_content[i], "\t");
		ft_printf("After trimmed : %s\n", trimmed); //test
		if (ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			i++;
			continue;
		}
		if (is_map_start(trimmed))
		{
			ft_printf("found map at line : %s\n", trimmed); //test
			free(trimmed);
			break;
		}
		parse_line(trimmed, &data->config);
		free(trimmed);
		i++;
	}
	if (!all_elements_set(&data->config))
		ft_error("Missing config elem");
	parse_map(split_content, i, data);
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
	if (!check_extension(filename))
		return (write(2, "error, bad extension\n", 22), 0);
	if ((content = read_file(filename)) == NULL)
		return (write(2, "error, bad read\n", 17), 0);
	ft_printf("print of content before first split : \n%s\n", content); //test
	split_content = ft_split(content, '\n');
	free(content);
	process_lines(split_content, data);
	return (1);
}
