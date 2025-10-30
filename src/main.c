/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:17:40 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/30 20:48:56 by abidaux          ###   ########.fr       */
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
	player->pos_x = 3.5;
	player->pos_y = 3.5;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
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
	init_player(&data->player);
	return (1);
}

/*
** ft_error : affiche un message d'erreur et quitte
*/
void	ft_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, 0);
	while (msg && *msg)
	{
		write(2, msg, 1);
		msg++;
	}
	write(2, "\n", 1);
	exit(1);
}

/*
** cleanup : libère toutes les ressources MLX
*/
void	cleanup(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
}

/*
** close_window : appelé quand on ferme la fenêtre (croix rouge)
*/
int	close_window(t_data *data)
{
	cleanup(data);
	exit(0);
	return (0);
}

int	main(void)
{
	t_data	data;

	if (!init_data(&data))
		ft_error("Initialization failed");
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
