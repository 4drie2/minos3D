
#include "../include/cub3d.h"

void	validate_map_closed(t_config *config) //!!!!!!!!!
{
	char	**copy;

	copy = duplicate_map(config->map, config->map_height, config->map_width);
	flood_fill(copy, (int)config->player_x, (int)config->player_y, config); // Assume player_x/y stored
	check_edges(copy, config);
	ft_free_array(copy);
}

static void	find_player(t_config *config, int *player_count, int x, int y) //faut il uncomment here ?
{
	char	c;

	c = config->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		// Store in your main struct, e.g.
		// config->player_x = x + 0.5;
		// config->player_y = y + 0.5;
		// config->player_dir = c;
		config->map[y][x] = '0';
		(*player_count)++;
	}
}

static void	store_map_line(t_config *config, char *line, int y)
{
	int	x;

	config->map[y] = malloc(config->map_width + 1); // ici char mais nous int, why int? 
	if (!config->map[y])
		ft_error("Malloc fail");
	ft_memset(config->map[y], ' ', config->map_width);
	ft_strlcpy(config->map[y], line, ft_strlen(line) + 1); //!!!!!!!!!
	config->map[y][config->map_width] = '\0';
	x = 0;
	while (x < config->map_width)
	{
		if (!is_valid_map_char(config->map[y][x]))
			ft_error("Invalid map char");
		x++;
	}
}

void	parse_map(char **lines, int start, t_config *config)
{
	int	height;
	int	width;
	int	y;
	int	player_count;

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
	config->map = malloc(sizeof(char *) * (height + 1));
	if (!config->map)
		ft_error("Malloc fail");
	config->map_height = height;
	config->map_width = width;
	y = 0;
	player_count = 0;
	while (y < height)
	{
		store_map_line(config, lines[start + y], y);
		x = 0;
		while (x < width)
		{
			find_player(config, &player_count, x, y);
			x++;
		}
		y++;
	}
	config->map[height] = NULL;
	if (player_count != 1)
		ft_error("Invalid player count");
	validate_map_closed(config);
}