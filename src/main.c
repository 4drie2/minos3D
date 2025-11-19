/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:17:40 by abidaux           #+#    #+#             */
/*   Updated: 2025/11/19 16:09:57 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_parsing(t_data *data)
{
	init_player(&data->player);
	init_config(&data->config);
	data->split_content = NULL;
	data->filename = NULL;
	data->content = NULL;
	data->check_minil = 0;
	data->check_text = 0;
	data->check_err_pro_line = 0;
	data->chec_map_used = 0;
}

/*
** close_window : appelé quand on ferme la fenêtre (croix rouge)
*/
int	close_window(t_data *data)
{
	cleanup(data);
	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (write(2, "Not enough args\n", 16));
	init_parsing(&data);
	if (!parse_file(&data, argv[1]))
		ft_error("parsing failed", &data);
	ft_memset(&data.keys, 0, sizeof(t_keys));
	if (!init_data(&data))
		ft_error("Initialization failed", &data);
	if (!init_textures(&data))
		ft_error("Failed to load textures", &data);
	data.mouse.last_x = 0;
	data.mouse.last_y = 0;
	data.mouse.first_move = 1;
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_hook(data.win, MotionNotify, PointerMotionMask, mouse_move, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
