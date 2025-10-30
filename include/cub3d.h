/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:28:51 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/30 20:48:05 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "../libft/libft.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_player	player;
	int			**map;
	int			map_width;
	int			map_height;
}	t_data;

/* Init */
int		init_data(t_data *data);
void	init_player(t_player *player);

/* Render */
int		render_frame(t_data *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

/* Events */
int		key_press(int keycode, t_data *data);
int		close_window(t_data *data);

/* Utils */
void	ft_error(char *msg);
void	cleanup(t_data *data);
