/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:53:02 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/11 04:31:40 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#include "../include/cub3d.h"

/*
** render_frame : appelée à chaque frame
** Lance le raycasting et affiche l'image
**
** Optimisation : on réutilise la même image au lieu de la recréer
*/
int	render_frame(t_data *data)
{
	update_movement(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
