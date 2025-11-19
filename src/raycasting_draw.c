/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:02:30 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:56:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** draw_ceiling: draws the ceiling
*/
static void	draw_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;

	y = 0;
	color = (data->config.sky.r << 16) | (data->config.sky.g << 8)
		| data->config.sky.b;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

/*
** draw_wall: draws the wall with texture
*/
static void	draw_wall(t_data *data, t_ray *ray, int x)
{
	int		y;
	int		color;
	int		tex_y;
	double	step;
	double	tex_pos;

	step = 1.0 * data->textures[ray->tex_num].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (data->textures[ray->tex_num].height - 1);
		tex_pos += step;
		color = get_texture_color(&data->textures[ray->tex_num],
				ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

/*
** draw_floor: draws the floor
*/
static void	draw_floor(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;

	color = (data->config.floor.r << 16) | (data->config.floor.g << 8)
		| data->config.floor.b;
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

/*
** draw_vertical_line: draws a screen column with textures
**
** Ceiling (0 to draw_start) -> light blue
** Wall (draw_start to draw_end) -> texture
** Floor (draw_end to WIN_HEIGHT) -> dark gray
*/
void	draw_vertical_line(t_data *data, t_ray *ray, int x)
{
	draw_ceiling(data, ray, x);
	draw_wall(data, ray, x);
	draw_floor(data, ray, x);
}
