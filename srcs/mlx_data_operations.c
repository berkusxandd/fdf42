/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:48:00 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:46:34 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	destroy_mlx(t_mlx_data *mlx_data)
{
	if (mlx_data->img_data != NULL && mlx_data->img_data->img != NULL)
		mlx_destroy_image(mlx_data->mlx, mlx_data->img_data->img);
	if (mlx_data->win != NULL)
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	if (mlx_data->mlx != NULL)
		mlx_destroy_display(mlx_data->mlx);
	free(mlx_data->img_data);
	free_map(mlx_data);
	free(mlx_data->mlx);
	exit(1);
}

int	handle_input(int keysym, t_mlx_data *mlx_data)
{
	if (keysym == 0xff1b)
		destroy_mlx(mlx_data);
	if ((keysym == 0xffab || keysym == 0xffad) && mlx_data->keyboard.zoom == 1)
		zoom_menu(keysym, mlx_data);
	if (mlx_data->keyboard.translation == 1)
		translation_menu(keysym, mlx_data);
	if (mlx_data->keyboard.rotate == 1)
		rotation_menu(keysym, mlx_data);
	if (keysym == 0x007a || keysym == 0x0074 || keysym == 0x0072
		|| keysym == 0x0070)
	{
		if (keysym != 0x0070)
		{
			keyboard_init(&mlx_data->keyboard);
			mlx_data->map_data->projection = 0;
		}
		menu_key_handle(keysym, mlx_data);
	}
	update_image(mlx_data);
	return (0);
}

void	mlx_image_data_write(t_mlx_data *mlx_data)
{
	mlx_data->img_data = malloc(sizeof(t_img_data));
	if (mlx_data->img_data == NULL)
	{
		ft_putstr_fd("memory error\n", 2);
		free_map(mlx_data);
		exit(-1);
	}
	mlx_data->img_data->img = mlx_new_image(mlx_data->mlx, WIN_WIDTH,
			WIN_HEIGHT);
	if (mlx_data->img_data->img == NULL)
	{
		ft_putstr_fd("memory error\n", 2);
		destroy_mlx(mlx_data);
	}
	mlx_data->img_data->addr = mlx_get_data_addr(mlx_data->img_data->img,
			&(mlx_data->img_data->bits_per_pixel),
			&(mlx_data->img_data->line_length), &(mlx_data->img_data->endian));
	if (mlx_data->img_data->addr == NULL)
	{
		ft_putstr_fd("memory error\n", 2);
		destroy_mlx(mlx_data);
	}
}

void	mlx_data_write(t_mlx_data *mlx_data)
{
	mlx_data->map_data->projection = 0;
	mlx_data->map_data->start = 0;
	mlx_data->map_data->angle_x = 0;
	mlx_data->map_data->angle_y = 0;
	mlx_data->map_data->angle_z = 0;
	mlx_data->map_data->zoom_factor = zoom_factor_calc(mlx_data->map_data);
	mlx_data->mlx = mlx_init();
	if (mlx_data->mlx == NULL)
	{
		ft_putstr_fd("memory error\n", 2);
		free_map(mlx_data);
		free(mlx_data->img_data);
		exit(-1);
	}
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	if (mlx_data->win == NULL)
		mlx_memory_error(mlx_data);
	mlx_image_data_write(mlx_data);
	if (draw_map(mlx_data, &mlx_data->keyboard) == -1)
		mlx_memory_error(mlx_data);
	mlx_data->map_data->start = 1;
}

void	update_image(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img_data->img);
	free(mlx_data->img_data);
	mlx_data->img_data = malloc(sizeof(t_img_data));
	mlx_data->img_data->img = mlx_new_image(mlx_data->mlx, WIN_WIDTH,
			WIN_HEIGHT);
	mlx_data->img_data->addr = mlx_get_data_addr(mlx_data->img_data->img,
			&(mlx_data->img_data->bits_per_pixel),
			&(mlx_data->img_data->line_length), &(mlx_data->img_data->endian));
	mlx_data->img_data = mlx_data->img_data;
	if (draw_map(mlx_data, &mlx_data->keyboard) == -1)
	{
		ft_putstr_fd("memory error\n", 2);
		destroy_mlx(mlx_data);
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win,
		mlx_data->img_data->img, 0, 0);
}
