/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:04:24 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/04 17:50:23 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** cleanup_map : libère la map
*/
static void	cleanup_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->config.map_height)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

/*
** cleanup : libère toutes les ressources MLX
*/
void	cleanup(t_data *data)
{
	free_textures(data);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	cleanup_map(data);
}
