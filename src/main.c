/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:17:40 by abidaux           #+#    #+#             */
/*   Updated: 2025/10/31 18:55:04 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

	// if (argc != 2)
		// return (write(2, "Not enough args\n", 17));
	(void)argv;
	(void)argc;
	ft_memset(&data.keys, 0, sizeof(t_keys));
	if (!init_data(&data))
		ft_error("Initialization failed");
	if (!parse_file(&data, argv[1]))
		ft_error("parsing failed");
	if (!init_textures(&data))
		ft_error("Failed to load textures");
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
