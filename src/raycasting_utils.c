/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:03:43 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/12 09:54:54 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** calculate_wall_height : calcule la distance au mur et sa hauteur à l'écran
**
** 1. Calcule la distance PERPENDICULAIRE au mur (pas euclidienne)
**    pour éviter l'effet "fisheye" (distorsion)
** 2. Calcule la hauteur du mur à l'écran (plus proche = plus grand)
** 3. Détermine les limites verticales de dessin (draw_start/draw_end)
*/
void	calculate_wall_height(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/*
** calculate_texture_x : calcule la coordonnée x de la texture
**
** wall_x : position exacte où le rayon touche le mur (0.0 à 1.0)
** tex_x : coordonnée x dans la texture
** tex_num : quelle texture utiliser (0=NO, 1=SO, 2=EA, 3=WE)
*/
void	calculate_texture_x(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = data->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->tex_num = 2;
		else
			ray->tex_num = 3;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
	ray->tex_x = (int)(ray->wall_x
			* (double)data->textures[ray->tex_num].width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = data->textures[ray->tex_num].width - ray->tex_x - 1;
}
