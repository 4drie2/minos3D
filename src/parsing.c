/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 18:02:56 by abidaux          ###   ########.fr       */
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

int	parse_file(t_data *data, char *filename)
{
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
