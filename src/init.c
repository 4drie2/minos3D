/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:04:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:56:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** my_mlx_pixel_put: writes a pixel to the image
** We use the image's memory address to write directly
** Faster than mlx_pixel_put which refreshes at each call
*/
void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** init_player: initializes the player's position and direction
** pos: position (x, y) on the map
** dir: direction vector (where the player is looking)
** plane: camera plane (perpendicular to dir, defines the FOV)
*/
void	init_player(t_player *player)
{
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
}

void	init_config(t_config *config)
{
	config->no_text_path = NULL;
	config->so_text_path = NULL;
	config->we_text_path = NULL;
	config->ea_text_path = NULL;
	config->floor.r = -1;
	config->floor.g = -1;
	config->floor.b = -1;
	config->sky.r = -1;
	config->sky.g = -1;
	config->sky.b = -1;
	config->map_height = -1;
	config->map_width = -1;
	config->player_count = 0;
	return ;
}

/*
** init_data: initializes MLX and creates the window + image
** 1. Connection to the graphics server (mlx_init)
** 2. Creation of the window
** 3. Creation of the image where we will draw
** 4. Retrieval of the image's memory address
*/
int	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
		return (0);
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
	data->check_minil = 1;
	data->move_speed = MOVE_SPEED;
	return (1);
}

/*
** ft_error: displays an error message and exits
*/
void	ft_error(char *msg, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	cleanup(data);
	exit(1);
}
