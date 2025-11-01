/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:02:30 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 18:56:43 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** draw_ceiling : dessine le ciel
*/
static void	draw_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&data->img, x, y, 0x87CEEB); //changer la couleur par ce qu'il va etre donné dans le .cub
		y++;
	}
}

/*
** draw_wall : dessine le mur avec texture
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
** draw_floor : dessine le sol
*/
static void	draw_floor(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&data->img, x, y, 0x404040); //changer la couleur par ce qu'il va etre donné dans le .cub
		y++;
	}
}

/*
** draw_vertical_line : dessine une colonne de l'écran avec textures
**
** Ciel (0 à draw_start) -> bleu clair
** Mur (draw_start à draw_end) -> texture
** Sol (draw_end à WIN_HEIGHT) -> gris foncé
*/
void	draw_vertical_line(t_data *data, t_ray *ray, int x)
{
	draw_ceiling(data, ray, x);
	draw_wall(data, ray, x);
	draw_floor(data, ray, x);
}
