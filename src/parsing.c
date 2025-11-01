/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 18:55:55 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	allocate_map(t_data *data)
{
	int	i;

	data->map_height = 20;
	data->map_width = 30;
	data->map = malloc(sizeof(int *) * data->map_height);
	if (!data->map)
		return (0);
	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = malloc(sizeof(int) * data->map_width);
		if (!data->map[i])
			return (0);
		i++;
	}
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
		free(line);
	}
	close(fd);
	return (content);
}

int	parse_file(t_data *data, char *filename)
{
	//set up les path 

	char	*content;
	char	**split_content;

	content = NULL;
	split_content = NULL;
	if (!check_extension(char *filename))
		return (write(2, "error, bad extension\n", 22), 0);
	if ((content = read_file(char *filename)) == NULL)
		return (write(2, "error, bad read\n", 17), 0);
	split_content = ft_split(content, '\n');
	ft_printf("%s", content); //test
	free(content);





	int i;

	(void)filename; // Pour l'instant on ignore le fichier

	// Allocation de la map - a calculer...
	data->map_height = 8;
	data->map_width = 8;
	data->map = malloc(sizeof(int *) * data->map_height);
	if (!data->map)
		return (0);

	// Map test : 1 = mur, 0 = vide
	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = malloc(sizeof(int) * data->map_width);
		if (!data->map[i])
			return (0);
		i++;
	}

	// Remplissage manuel (map fermée avec un espace au centre)
	int temp_map[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};

	i = 0;
	while (i < 8)
	{
		int j = 0;
		while (j < 8)
		{
			data->map[i][j] = temp_map[i][j];
			j++;
		}
		i++;
	}

	return (1);
}
