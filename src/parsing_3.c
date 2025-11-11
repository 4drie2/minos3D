
#include "../include/cub3d.h"

static int	validate_map_closed(t_data *data, char **lines, int start)
{
	char	**copy;
	int		ret;

	ret = 0;
	if ((copy = duplicate_map(lines, data->config.map_height, start)) == NULL)
		return (write(2, "bad copy of map\n", 17), 0);
	flood_fill(copy, (int)data->player.pos_x, (int)data->player.pos_y, &ret);
	ft_free_array(copy);
	if (ret != 0)
		return (write(2, "map not good with flood_fill\n", 30), 0);
	return (1);
}

static void	find_player(t_data *data, int *player_count, int x, int y, char **lines)
{
	char	c;

	c = lines[y][x];
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
	data->player.pos_x = x;
	lines[y][x] = '0';
	(*player_count)++;
}

#include "cub3d.h"

static int	char_to_int(char c)
{
	if (c == '1')
		return (1);
	if (c == '0' || c == ' ')
		return (0);
	return (0);
}

static void	map_to_int(t_data *data, char **lines, int start)
{
	int	y;
	int	x;
	int	len;

	data->map = malloc(sizeof(int *) * data->config.map_height);
	if (!data->map)
		ft_error("Malloc failed for map_int", &data);
	y = 0;
	while (y < data->config.map_height)
	{
		data->map[y] = malloc(sizeof(int) * data->config.map_width);
		if (!data->map[y])
			ft_error("Malloc failed for map_int[y]", &data);
		len = ft_strlen(lines[start + y]);
		x = 0;
		while (x < data->config.map_width)
		{
			if (x < len)
				data->map[y][x] = char_to_int(lines[start + y][x]);
			else
				data->map[y][x] = 0;
			x++;
		}
		y++;
	}
}

int	parse_map(char **lines, int start, t_data *data)
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
	data->config.map_height = height;
	data->config.map_width = width;
	y = 0;
	player_count = 0;
	while (y < height)	
	{
		x = 0;
		while (x < width && lines[y + start][x])
		{
			find_player(data, &player_count, x, start + y, lines);
			if (data->player.pos_x != -1 && data->player.pos_y == -1)
				data->player.pos_y = y;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (write(2, "Invalid player count\n", 22), 0);
	if (!validate_map_closed(data, lines, start))
		return (write(2, "Invalid map\n", 13), 0);
	map_to_int(data, lines, start);
}
