/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:11:17 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 14:48:49 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** move_forward : déplace le joueur en avant
** Vérifie qu'on ne rentre pas dans un mur
*/
void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;

	if (data->map[(int)data->player.pos_y][(int)new_x] == 0)
		data->player.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->player.pos_x] == 0)
		data->player.pos_y = new_y;
}

/*
** move_backward : déplace le joueur en arrière
*/
void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;

	if (data->map[(int)new_y][(int)new_x] == 0)
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

/*
** rotate_left : fait tourner le joueur à gauche
** Rotation de la direction ET du plan caméra
**
** Formule de rotation 2D :
** new_x = old_x * cos(angle) - old_y * sin(angle)
** new_y = old_x * sin(angle) + old_y * cos(angle)
*/
void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROT_SPEED) -
						data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(ROT_SPEED) +
						data->player.dir_y * cos(ROT_SPEED);

	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROT_SPEED) -
							data->player.plane_y * sin(ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(ROT_SPEED) +
							data->player.plane_y * cos(ROT_SPEED);
}

/*
** rotate_right : fait tourner le joueur à droite
*/
void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED) -
						data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(-ROT_SPEED) +
						data->player.dir_y * cos(-ROT_SPEED);

	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED) -
							data->player.plane_y * sin(-ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(-ROT_SPEED) +
							data->player.plane_y * cos(-ROT_SPEED);
}

/*
** move_left : déplace le joueur vers la gauche (strafe)
** Utilise le vecteur perpendiculaire à la direction (plane)
*/
void	move_left(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
    new_y = data->player.pos_y - data->player.plane_y * MOVE_SPEED;

    if (data->map[(int)data->player.pos_y][(int)new_x] == 0)
        data->player.pos_x = new_x;
    if (data->map[(int)new_y][(int)data->player.pos_x] == 0)
        data->player.pos_y = new_y;
}

/*
** move_right : déplace le joueur vers la droite (strafe)
*/
void	move_right(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
    new_y = data->player.pos_y + data->player.plane_y * MOVE_SPEED;

    if (data->map[(int)data->player.pos_y][(int)new_x] == 0)
        data->player.pos_x = new_x;
    if (data->map[(int)new_y][(int)data->player.pos_x] == 0)
        data->player.pos_y = new_y;
}
