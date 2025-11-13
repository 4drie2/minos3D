/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adrien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:28:51 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/13 10:28:14 by adrien           ###   ########.fr       */
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

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

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
	char	player_dir;
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

typedef struct t_colors
{
	int	r;
	int	g;
	int	b;
}	t_colors;


typedef struct s_config
{
	char		*no_text_path;
	char		*so_text_path;
	char		*we_text_path;
	char		*ea_text_path;
	int			map_width;
	int			map_height;
	t_colors		floor;
	t_colors		sky;
}	t_config;

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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_player	player;
	int			**map;
	t_keys		keys;
	t_texture	textures[4];
	t_config	config;
	char		**split_content;
	char		*filename;
	char		*content;
	t_ray		ray;
	int			check_text;
	int			check_minil;
	int			check_err_pro_line;
}	t_data;

// Main
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	ft_error(char *msg, t_data *data);
void	cleanup(t_data *data);
int		close_window(t_data *data);

/* init.c */
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	init_player(t_player *player);
int		init_data(t_data *data);
void	init_config(t_config *config);

// Events
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	update_movement(t_data *data);

/* cleanup.c */
void	cleanup(t_data *data);

// Render
int		render_frame(t_data *data);

// Raycasting
void	cast_rays(t_data *data);
void	free_config_struc(t_config *config);

/* raycasting_utils.c */
void	calculate_wall_height(t_data *data, t_ray *ray);
void	calculate_texture_x(t_data *data, t_ray *ray);

/* raycasting_draw.c */
void	draw_vertical_line(t_data *data, t_ray *ray, int x);

/* Parsing */
int		parse_file(t_data *data, char *filename);
int		is_map_start(char *line);
int		parse_line(char *line, t_config *config);
int		ft_array_len(char **array);
void	ft_free_array(char **array);
int		parse_map(char **lines, int start, t_data *data);
int		is_valid_map_char(char c);
char	**duplicate_map(char **map, int height, int start);
void	flood_fill(char **map, int x, int y, int *ret);
void	check_edges(char **copy, t_config *config);

/* Player */
void	rotate_player(t_player *player, double angle);
void	move_player(t_data *data, double move_x, double move_y);
void	handle_rotation(t_data *data);
void	handle_movement(t_data *data);
void	handle_strafe_movement(t_data *data, double move_speed);

/* player_move.c */
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

// Textures
int		init_textures(t_data *data);
int		load_texture(t_data *data, t_texture *texture, char *path);
void	free_textures(t_data *data);
int		get_texture_color(t_texture *texture, int x, int y);
