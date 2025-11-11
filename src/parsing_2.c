/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:22:18 by plerick           #+#    #+#             */
/*   Updated: 2025/11/11 20:28:51 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

static void	parse_color(char *str, t_colors *color, int *err)
{
	char	**rgb;

	*err = 0;
	rgb = ft_split(str, ',');
	if (!rgb)
	{
		return ((void)write(2, "bad split parscol\n", 18));
	}
	if (ft_array_len(rgb) != 3)
	{
		ft_free_array(rgb);
		return ((void)write(2, "Invalid color format\n", 21));
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		ft_free_array(rgb);
		return ((void)write(2, "Color out of range\n", 19));
	}
	*err = 1;
	ft_free_array(rgb);
}

static void	validate_texture(char *path, int *err)
{
	int	fd;

	*err = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Texture file not found\n", 23);
		return ;
	}
	*err = 1;
	close(fd);
}

static void	parse_texture(char **split, t_config *config, int *err)
{
	if (ft_strcmp(split[0], "NO") == 0 && !config->no_text_path)
	{
		config->no_text_path = ft_strdup(split[1]);
		validate_texture(config->no_text_path, err);
	}
	else if (ft_strcmp(split[0], "SO") == 0 && !config->so_text_path)
	{
		config->so_text_path = ft_strdup(split[1]);
		validate_texture(config->so_text_path, err);
	}
	else if (ft_strcmp(split[0], "WE") == 0 && !config->we_text_path)
	{
		config->we_text_path = ft_strdup(split[1]);
		validate_texture(config->we_text_path, err);
	}
	else if (ft_strcmp(split[0], "EA") == 0 && !config->ea_text_path)
	{
		config->ea_text_path = ft_strdup(split[1]);
		validate_texture(config->ea_text_path, err);
	}
	else
	{
		write(2, "Invalid or duplicate texture\n", 29);
		*err = 0;
	}
}

int	parse_line(char *line, t_config *config)
{
	char	**split;
	int		err;

	err = 1;
	split = ft_split(line, ' ');
	if (!split)
		return (write(2, "bad split\n", 10), 0);
	if (ft_array_len(split) != 2)
	{
		ft_free_array(split);
		return (write(2, "Invalid config line", 19), 0);
	}
	if (ft_strcmp(split[0], "NO") == 0 || ft_strcmp(split[0], "SO") == 0
		|| ft_strcmp(split[0], "WE") == 0 || ft_strcmp(split[0], "EA") == 0)
		parse_texture(split, config, &err);
	else if (ft_strcmp(split[0], "F") == 0 && config->floor.r == -1)
		parse_color(split[1], &config->floor, &err);
	else if (ft_strcmp(split[0], "C") == 0 && config->sky.r == -1)
		parse_color(split[1], &config->sky, &err);
	else
	{
		
		return (ft_free_array(split), write(2, "Invalid or duplicate config", 27), 0);
	}
	ft_free_array(split);
	return (err);
}
