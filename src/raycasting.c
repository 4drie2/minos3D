/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:03:15 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 14:06:10 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/cub3d.h"


/*
** perform_dda : algorithme DDA (Digital Differential Analysis)
** Parcourt la map case par case jusqu'à toucher un mur
**
** Principe :
** - On avance case par case dans la direction du rayon
** - step_x/y : direction de déplacement (+1 ou -1)
** - side_dist : distance au prochain bord de case
** - delta_dist : distance entre 2 bords de case
*/
void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		// Avance dans la direction la plus proche
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Mur vertical (Nord/Sud)
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Mur horizontal (Est/Ouest)
		}

		// Vérifie si on touche un mur
		if (data->map[ray->map_y][ray->map_x] > 0)
			hit = 1;
	}
}

/*
** init_ray : initialise les données du rayon pour une colonne x
**
** camera_x : position x sur le plan de la caméra (-1 à +1)
** ray_dir : direction du rayon (dir + plane * camera_x)
** delta_dist : distance entre 2 intersections de grille
*/
void	init_ray(t_data *data, t_ray *ray, int x)
{
	double	camera_x;

	// Position sur le plan caméra : -1 (gauche) à +1 (droite)
	camera_x = 2 * x / (double)WIN_WIDTH - 1;

	// Direction du rayon = direction joueur + plan caméra
	ray->dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray->dir_y = data->player.dir_y + data->player.plane_y * camera_x;

	// Case de la map où se trouve le joueur
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;

	// Distance pour traverser une case entière
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

/*
** init_step : calcule la direction et distance initiale
**
** step : +1 ou -1 (direction de déplacement dans la grille)
** side_dist : distance jusqu'au premier bord de case
*/
void	init_step(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->delta_dist_x;
	}

	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y) * ray->delta_dist_y;
	}
}

/*
** calculate_wall_distance : calcule la distance perpendiculaire au mur
**
** ⚠️ On utilise la distance PERPENDICULAIRE (pas euclidienne)
** Sinon effet "fisheye" (distorsion)
*/
void	calculate_wall_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos_x +
								(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos_y +
								(1 - ray->step_y) / 2) / ray->dir_y;
}

/*
** calculate_line_height : calcule la hauteur du mur à l'écran
**
** Plus le mur est proche, plus il est grand
** line_height = hauteur_écran / distance
*/
void	calculate_line_height(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);

	// Point de départ (haut du mur)
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;

	// Point de fin (bas du mur)
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/*
** draw_vertical_line : dessine une colonne de l'écran
**
** Ciel (0 à draw_start) → bleu clair
** Mur (draw_start à draw_end) → couleur selon orientation
** Sol (draw_end à WIN_HEIGHT) → gris foncé
*/
void	draw_vertical_line(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;

	// Couleur du mur selon l'orientation
	if (ray->side == 1)
		color = 0xFF0000; // Rouge (Est/Ouest)
	else
		color = 0x00FF00; // Vert (Nord/Sud)

	// Assombrir les murs horizontaux pour effet de profondeur
	if (ray->side == 1)
		color = color / 2;

	// Dessine le ciel
	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&data->img, x, y, 0x87CEEB);
		y++;
	}

	// Dessine le mur
	while (y <= ray->draw_end)
	{
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}

	// Dessine le sol
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&data->img, x, y, 0x404040);
		y++;
	}
}

/*
** cast_rays : fonction principale du raycasting
** Lance un rayon pour chaque colonne de l'écran
*/
void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		init_step(data, &ray);
		perform_dda(data, &ray);
		calculate_wall_distance(data, &ray);
		calculate_line_height(&ray);
		draw_vertical_line(data, &ray, x);
		x++;
	}
}
