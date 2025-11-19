/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:03:43 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:56:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** calculate_wall_height: calculates the distance to the wall and its screen height
**
** 1. Calculates the PERPENDICULAR distance to the wall (not euclidean)
**    to avoid the "fisheye" effect (distortion)
** 2. Calculates the wall height on screen (closer = larger)
** 3. Determines the vertical drawing limits (draw_start/draw_end)
*/
void	calculate_wall_height(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->line_height > WIN_HEIGHT * 10)
		ray->line_height = WIN_HEIGHT * 10;
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/*
** calculate_texture_x: calculates the x coordinate of the texture
**
** wall_x: exact position where the ray hits the wall (0.0 to 1.0)
** tex_x: x coordinate in the texture
** tex_num: which texture to use (0=NO, 1=SO, 2=EA, 3=WE)
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
