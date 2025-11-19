/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:10:45 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:56:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** load_texture: loads an XPM texture from a file
** Uses mlx_xpm_file_to_image to load the image
** Retrieves the memory address to access the pixels
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
** free_textures: frees all loaded textures
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
** get_texture_color: retrieves the color of a pixel in a texture
** x, y: coordinates of the pixel in the texture
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
