/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:04:24 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/12 20:08:27 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_config_struc(t_config *config)
{
	if (config->no_text_path)
		free(config->no_text_path);
	if (config->so_text_path)
		free(config->so_text_path);
	if (config->we_text_path)
		free(config->we_text_path);
	if (config->ea_text_path)
		free(config->ea_text_path);
}

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
	if (!data)
		return ;
	if (data->check_text == 1)
		free_textures(data);
	if (data->check_minil == 1)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->check_minil == 1)
		mlx_destroy_window(data->mlx, data->win);
	if (data->check_minil == 1)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->check_err_pro_line == 0)
		free_config_struc(&data->config);
	cleanup_map(data);
}
