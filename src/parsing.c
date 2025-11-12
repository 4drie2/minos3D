/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/12 19:27:11 by plerick          ###   ########.fr       */
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

static int	process_lines(char **split_content, t_data *data)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (split_content[i])
	{
		trimmed = ft_strdup(split_content[i]);	
		if (is_map_start(trimmed))
		{
			free(trimmed);
			break;
		}
		if (!(parse_line(trimmed, &data->config)))
		{
			free(trimmed);
			data->check_err_pro_line = 1;
			return(free_config_struc(&data->config), write(2, "error in parsing\n", 17), 0);
		}
		free(trimmed);
		i++;
	}
	if (!all_elements_set(&data->config))
		return (write(2, "Missing config elem\n", 20), 0);
	if (!parse_map(split_content, i, data))
		return (write(2, "bad parse of map\n", 17), 0);
	return (1);
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
		return (write(2, "error, bad extension\n", 21), 0);
	if ((content = read_file(filename)) == NULL)
		return (write(2, "error, bad read\n", 16), 0);
	data->content = content;
	if (!(split_content = ft_split(content, '\n')))
		return (write(2, "bad split\n", 10), 0);
	data->split_content = split_content;
	free(content);
	if (!(process_lines(split_content, data)))
		return (ft_free_array(split_content), 0);
	ft_free_array(split_content);
	return (1);
}
