/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:28:51 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 16:08:45 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_player	player;
	int			**map;
	int			map_width;
	int			map_height;
	t_keys		keys;
	t_texture	textures[4];
}	t_data;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_num;
	int		tex_x;
}	t_ray;

// Main
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	ft_error(char *msg);
void	cleanup(t_data *data);
int		close_window(t_data *data);

// Events
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	update_movement(t_data *data);

// Render
int		render_frame(t_data *data);

// Raycasting
void	cast_rays(t_data *data);

// player
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);

// Parsing (temporaire)
int		parse_file(t_data *data, char *filename);

// Textures
int		init_textures(t_data *data);
int		load_texture(t_data *data, t_texture *texture, char *path);
void	free_textures(t_data *data);
int		get_texture_color(t_texture *texture, int x, int y);
