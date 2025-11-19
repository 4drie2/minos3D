/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:03:15 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:56:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** perform_dda: DDA algorithm (Digital Differential Analysis)
** Traverses the map cell by cell until hitting a wall
**
** Principle:
** - We advance cell by cell in the direction of the ray
** - step_x/y: direction of movement (+1 or -1)
** - side_dist: distance to the next cell edge
** - delta_dist: distance between 2 cell edges
*/
void	perform_dda(t_data *data, t_ray *ray)
{
	while (true)
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
			break ;
	}
}

/*
** init_ray: initializes the ray data for a column x
**
** camera_x: x position on the camera plane (-1 to +1)
** ray_dir: direction of the ray (dir + plane * camera_x)
** delta_dist: distance between 2 grid intersections
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
** init_step: calculates the direction and initial distance
**
** step: +1 or -1 (direction of movement in the grid)
** side_dist: distance to the first cell edge
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
** cast_rays: main raycasting function
** Casts a ray for each column of the screen
*/
void	cast_rays(t_data *data)
{
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &data->ray, x);
		init_step(data, &data->ray);
		perform_dda(data, &data->ray);
		calculate_wall_height(data, &data->ray);
		calculate_texture_x(data, &data->ray);
		draw_vertical_line(data, &data->ray, x);
		x++;
	}
}

/*
** render_frame: called at each frame
** Launches the raycasting and displays the image
**
** Optimization: we reuse the same image instead of recreating it
*/
int	render_frame(t_data *data)
{
	update_movement(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	if (MOUSE_SENSITIVITY != 0.0)
		mlx_mouse_hide(data->mlx, data->win);
	if (MOUSE_SENSITIVITY != 0.0)
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}
