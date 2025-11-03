
#include "../include/cub3d.h"

char	**duplicate_map(char **map, int height, int width)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		ft_error("Malloc fail");
	y = 0;
	while (y < height)
	{
		copy[y] = ft_strdup(map[y]);
		y++;
	}
	copy[height] = NULL;
	return (copy);
}

void	flood_fill(char **map, int x, int y, t_config *config)
{
	if (x < 0 || x >= config->map_width || y < 0 || y >= config->map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == ' ' || map[y][x] == '0')
		map[y][x] = 'X';
	flood_fill(map, x + 1, y, config);
	flood_fill(map, x - 1, y, config);
	flood_fill(map, x, y + 1, config);
	flood_fill(map, x, y - 1, config);
}

void	check_edges(char **copy, t_config *config)
{
	int	y;
	int	x;

	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (copy[y][x] == '0' || copy[y][x] == ' ')
			{
				if (x == 0 || x == config->map_width - 1
					|| y == 0 || y == config->map_height - 1)
					ft_error("Map not closed");
			}
			x++;
		}
		y++;
	}
}
