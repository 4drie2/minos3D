

#include "../include/cub3d.h"

static void	parse_color(char *str, t_colors *color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str, ',');
	if (ft_array_len(rgb) != 3)
		ft_error("Invalid color format");
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		ft_error("Color out of range");
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

static void	validate_texture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("Texture file not found");
	close(fd);
}

static void	parse_texture(char **split, t_config *config)
{
	if (ft_strcmp(split[0], "NO") == 0 && !config->no_text_path)
	{
		config->no_text_path = ft_strdup(split[1]);
		validate_texture(config->no_text_path);
	}
	else if (ft_strcmp(split[0], "SO") == 0 && !config->so_text_path)
	{
		config->so_text_path = ft_strdup(split[1]);
		validate_texture(config->so_text_path);
	}
	else if (ft_strcmp(split[0], "WE") == 0 && !config->we_text_path)
	{
		config->we_text_path = ft_strdup(split[1]);
		validate_texture(config->we_text_path);
	}
	else if (ft_strcmp(split[0], "EA") == 0 && !config->ea_text_path)
	{
		config->ea_text_path = ft_strdup(split[1]);
		validate_texture(config->ea_text_path);
	}
	else
		ft_error("Invalid or duplicate texture");
}

void	parse_line(char *line, t_config *config)
{
	char	**split;

	split = ft_split(line, ' ');
	if (ft_array_len(split) != 2)
		ft_error("Invalid config line");
	if (ft_strcmp(split[0], "NO") == 0 || ft_strcmp(split[0], "SO") == 0
		|| ft_strcmp(split[0], "WE") == 0 || ft_strcmp(split[0], "EA") == 0)
		parse_texture(split, config);
	else if (ft_strcmp(split[0], "F") == 0 && config->floor.r == -1)
		parse_color(split[1], &config->floor);
	else if (ft_strcmp(split[0], "C") == 0 && config->sky.r == -1)
		parse_color(split[1], &config->sky);
	else
		ft_error("Invalid or duplicate config");
	ft_free_array(split);
}
