/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/18 19:14:24 by abidaux          ###   ########.fr       */
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

static int	process_config(char **split_content, t_data *data, int *map_start)
{
	int		i;
	char	*trimmed;

	i = -1;
	while (split_content[++i])
	{
		trimmed = ft_strdup(split_content[i]);
		if (is_map_start(trimmed))
		{
			free(trimmed);
			break ;
		}
		if (!(parse_line(trimmed, &data->config)))
		{
			free(trimmed);
			data->check_err_pro_line = 1;
			return (free_config_struc(&data->config), write(2, "par\n", 4), 0);
		}
		free(trimmed);
	}
	*map_start = i;
	return (1);
}

static int	validate_and_parse_map(char **split_content, int i, t_data *data)
{
	if (!all_elements_set(&data->config))
		return (write(2, "Missing config elem\n", 20), 0);
	if (!check_empty_lines_in_map(split_content, i, data))
		return (write(2, "empty line in map\n", 18), 0);
	if (!parse_map(split_content, i, data))
		return (write(2, "bad parse of map\n", 17), 0);
	return (1);
}

int	parse_file(t_data *data, char *filename)
{
	char	*content;
	char	**split_content;
	int		map_start;

	content = NULL;
	split_content = NULL;
	if (!check_extension(filename))
		return (write(2, "error, bad extension\n", 21), 0);
	content = read_file(filename);
	if (content == NULL)
		return (write(2, "error, bad read\n", 16), 0);
	data->content = content;
	split_content = ft_split(content, '\n');
	if (!split_content)
		return (write(2, "bad split\n", 10), 0);
	data->split_content = split_content;
	if (!(process_config(split_content, data, &map_start)))
		return (ft_free_array(split_content), 0);
	if (!(validate_and_parse_map(split_content, map_start, data)))
		return (ft_free_array(split_content), 0);
	ft_free_array(split_content);
	return (1);
}
