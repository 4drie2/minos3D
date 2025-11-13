/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:10:45 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/13 17:14:58 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** load_texture : charge une texture XPM depuis un fichier
** Utilise mlx_xpm_file_to_image pour charger l'image
** Récupère l'adresse mémoire pour accéder aux pixels
*/
int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_printf("Error: Failed to load texture: %s\n", path);
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(data->mlx, texture->img);
		return (0);
	}
	return (1);
}

int	init_textures(t_data *data)
{
	int		i;
	char	*paths[4];

	paths[0] = data->config.no_text_path;
	paths[1] = data->config.so_text_path;
	paths[2] = data->config.we_text_path;
	paths[3] = data->config.ea_text_path;
	i = 0;
	while (i < 4)
	{
		data->textures[i].img = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!load_texture(data, &data->textures[i], paths[i]))
		{
			free_textures(data);
			return (0);
		}
		i++;
	}
	data->check_text = 1;
	return (1);
}

/*
** free_textures : libère toutes les textures chargées
*/
void	free_textures(t_data *data)
{
	int	i;

	if (!data->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (data->textures[i].img)
		{
			mlx_destroy_image(data->mlx, data->textures[i].img);
			data->textures[i].img = NULL;
		}
		i++;
	}
}

/*
** get_texture_color : récupère la couleur d'un pixel dans une texture
** x, y : coordonnées du pixel dans la texture
*/
int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}
