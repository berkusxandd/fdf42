/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:24 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 17:50:37 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keyboard_init(t_keyboard *kb)
{
	kb->zoom = 0;
	kb->rotate = 0;
	kb->translation = 0;
}

int	handle_no_event(void)
{
	return (0);
}

void	mlx_data_init(t_mlx_data *mlx_data)
{
	mlx_data->map_data = NULL;
	mlx_data->img_data = NULL;
	mlx_data->win = NULL;
	mlx_data->map_data = NULL;
	mlx_data->img_data = NULL;
	mlx_data->win = NULL;
	mlx_data->keyboard.zoom = 0;
	mlx_data->keyboard.rotate = 0;
	mlx_data->keyboard.translation = 0;
}

int	close_button(t_mlx_data *mlx_data)
{
	destroy_mlx(mlx_data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mlx_data	mlx_data;
	int			map_parse_check;

	param_error(ac, env);
	mlx_data_init(&mlx_data);
	mlx_data.map_data = malloc(sizeof(t_map_data));
	map_parse_check = map_parse(av[1], mlx_data.map_data);
	if (mlx_data.map_data == NULL || map_parse_check != 1)
	{
		if (map_parse_check == -2)
			ft_putstr_fd("map error\n", 2);
		else
			ft_putstr_fd("memory error\n", 2);
		free_map(&mlx_data);
		exit(-1);
	}
	mlx_data_write(&mlx_data);
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img_data->img,
		0, 0);
	mlx_hook(mlx_data.win, 17, 1L << 0, close_button, &mlx_data);
	mlx_key_hook(mlx_data.win, handle_input, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, &handle_no_event, &mlx_data);
	mlx_loop(mlx_data.mlx);
	destroy_mlx(&mlx_data);
}
