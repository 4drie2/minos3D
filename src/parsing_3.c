
#include "../include/cub3d.h"

static void	validate_map_closed(t_data *data)
{
	char	**copy;

	copy = duplicate_map((char **)data->map, data->config.map_height, data->config.map_width);
	flood_fill(copy, (int)data->player.pos_x, (int)data->player.pos_y, &data->config);
	check_edges(copy, &data->config);
	ft_free_array(copy);
}

static void	find_player(t_data *data, int *player_count, int x, int y, char **lines)
{
	char	c;

	c = lines[y][x];
	printf("%c", c);
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
	data->player.pos_y = y;
	lines[y][x] = '0';
	(*player_count)++;
}

static void	store_map_line(t_data *data, char *line, int y) // Refaire la fonction et la placer à la fin du parsing pour juste copier la map d'un coup si tout est ok
{
	int	x;

	data->map[y] = malloc(data->config.map_width);
	if (!data->map[y])
		ft_error("Malloc fail");
	ft_memset(data->map[y], ' ', data->config.map_width);
	// ft_strlcpy(data->map[y], line, ft_strlen(line)); // ici peut être pb car line = char * et que data.map = int *, faut il utiliser atoi?
	// data->map[y][data->config.map_width] = '\0'; //useless in int *
	x = 0;
	while (x < data->config.map_width)
	{
		// ft_printf("before is_valid_map_char")
		if (!is_valid_map_char(line[x])) // à changer aussi pour le int * // pourquoi déjàa dans data->map, je peux juste check ce qu'il y a sur la ligne??
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
	int	i;

	height = 0;
	width = 0;
	y = start;
	i = 0;
	while(lines[i])
	{
		printf("%s\n", lines[i]);
		i++;
	}
	printf("eeeend\n");
	while (lines[y])
	{
		if (ft_strlen(lines[y]) > (size_t)width)
			width = ft_strlen(lines[y]);
		height++;
		y++;
	}
	// data->map = malloc(sizeof(int *) * (height));
	// if (!data->map)
	// 	ft_error("Malloc fail");
	data->config.map_height = height;
	data->config.map_width = width;
	y = 0;
	player_count = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			find_player(data, &player_count, x, start + y, lines);
			x++;
		}
		printf("\n");
		y++;
	}
	// data->map[height] = NULL; //utile dans int *?
	printf("player count : %i\n", player_count);
	if (player_count != 1)
		ft_error("Invalid player count");
	validate_map_closed(data);
	y = 0;
	store_map_line(data, lines[start + y], y);
}
