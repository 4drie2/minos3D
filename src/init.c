/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plerick <plerick@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:04:49 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/13 17:24:26 by plerick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** my_mlx_pixel_put : écrit un pixel dans l'image
** On utilise l'adresse mémoire de l'image pour écrire directement
** Plus rapide que mlx_pixel_put qui rafraîchit à chaque appel
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
** init_player : initialise la position et direction du joueur
** pos : position (x, y) dans la carte
** dir : vecteur direction (où regarde le joueur)
** plane : plan de la caméra (perpendiculaire à dir, définit le FOV)
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
** init_data : initialise MLX et crée la fenêtre + image
** 1. Connexion au serveur graphique (mlx_init)
** 2. Création de la fenêtre
** 3. Création de l'image où on va dessiner
** 4. Récupération de l'adresse mémoire de l'image
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
** ft_error : affiche un message d'erreur et quitte
*/
void	ft_error(char *msg, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	cleanup(data);
	exit(1);
}
