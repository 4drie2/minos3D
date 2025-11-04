
#include "../include/cub3d.h"

static void	validate_map_closed(t_data *data)
{
	char	**copy;

	copy = duplicate_map((char **)data->map, data->config.map_height, data->config.map_width);
	flood_fill(copy, (int)data->player.pos_x, (int)data->player.pos_y, &data->config);
	check_edges(copy, &data->config);
	ft_free_array(copy);
}

static void	find_player(t_data *data, int *player_count, int x, int y)
{
	char	c;

	c = data->map[y][x];
	if (!(c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return ;
	if (c == 'N')
	{
		data->player.dir_x = -1.0;
		data->player.dir_y = 0.0;
		data->player.plane_x = 0.0;
		data->player.plane_y = 0.66;
	}
	else if (c == 'S')
	{
		data->player.dir_x = 1.0;
		data->player.dir_y = 0.0;
		data->player.plane_x = 0.0;
		data->player.plane_y = -0.66;
	}
	else if (c == 'E')
	{
		data->player.dir_x = 0.0;
		data->player.dir_y = 1.0;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0.0;
	}
	else if (c == 'W')
	{
		data->player.dir_x = 0.0;
		data->player.dir_y = -1.0;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0.0;
	}
	data->map[y][x] = '0';
	(*player_count)++;
}

static void	store_map_line(t_data *data, char *line, int y)
{
	int	x;

	data->map[y] = malloc(data->config.map_width + 1);
	if (!data->map[y])
		ft_error("Malloc fail");
	ft_memset(data->map[y], ' ', data->config.map_width);
	ft_strlcpy((char *)data->map[y], line, ft_strlen(line) + 1);
	data->map[y][data->config.map_width] = '\0';
	x = 0;
	while (x < data->config.map_width)
	{
		if (!is_valid_map_char((char)data->map[y][x]))
			ft_error("Invalid map char");
		x++;
	}
}

void	parse_map(char **lines, int start, t_data *data)
{
	int	height;
	int	width;
	int	y;
	int	player_count;
	int	x;

	height = 0;
	width = 0;
	y = start;
	while (lines[y])
	{
		if (ft_strlen(lines[y]) > (size_t)width)
			width = ft_strlen(lines[y]);
		height++;
		y++;
	}
	data->map = malloc(sizeof(char *) * (height + 1));
	if (!data->map)
		ft_error("Malloc fail");
	data->config.map_height = height;
	data->config.map_width = width;
	y = 0;
	player_count = 0;
	while (y < height)
	{
		store_map_line(data, lines[start + y], y);
		x = 0;
		while (x < width)
		{
			find_player(data, &player_count, x, y);
			x++;
		}
		y++;
	}
	data->map[height] = NULL;
	if (player_count != 1)
		ft_error("Invalid player count");
	validate_map_closed(data);
}
