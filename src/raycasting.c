/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:03:15 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 18:56:59 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
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

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray->dir_y = data->player.dir_y + data->player.plane_y * camera_x;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
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
		ray->side_dist_x = (data->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_dist_y;
	}
}

/*
** calculate_wall_distance : calcule la distance perpendiculaire au mur
**
** On utilise la distance PERPENDICULAIRE (pas euclidienne)
** Sinon effet "fisheye" (distorsion)
*/
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
		calculate_texture_x(data, &ray);
		draw_vertical_line(data, &ray, x);
		x++;
	}
}
