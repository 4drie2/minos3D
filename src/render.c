/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:53:02 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 14:25:26 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#include "../include/cub3d.h"

/*
** render_frame : appelée à chaque frame
** Lance le raycasting et affiche l'image
*/
int	render_frame(t_data *data)
{
	// Détruire l'ancienne image et en créer une nouvelle
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);

	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);

	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
