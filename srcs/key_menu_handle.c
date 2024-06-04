/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_menu_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:15 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:45:25 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_menu(int keysym, t_mlx_data *mlx_data)
{
	if (keysym == 0xffab && mlx_data->keyboard.zoom == 1)
		mlx_data->map_data->zoom_factor += mlx_data->map_data->zoom_factor / 2;
	if (keysym == 0xffad && mlx_data->keyboard.zoom == 1)
	{
		if (mlx_data->map_data->zoom_factor - mlx_data->map_data->zoom_factor
			/ 2 != 1)
			mlx_data->map_data->zoom_factor -= mlx_data->map_data->zoom_factor
				/ 2;
	}
}

void	translation_menu(int keysym, t_mlx_data *mlx_data)
{
	if (keysym == 0xff53)
		mlx_data->map_data->x_offset -= mlx_data->map_data->zoom_factor;
	if (keysym == 0xff51)
		mlx_data->map_data->x_offset += mlx_data->map_data->zoom_factor;
	if (keysym == 0xff52)
		mlx_data->map_data->y_offset += mlx_data->map_data->zoom_factor;
	if (keysym == 0xff54)
		mlx_data->map_data->y_offset -= mlx_data->map_data->zoom_factor;
}

void	rotation_menu(int keysym, t_mlx_data *mlx_data)
{
	if (keysym == 0xff53)
		mlx_data->map_data->angle_y -= 0.1;
	if (keysym == 0xff51)
		mlx_data->map_data->angle_y += 0.1;
	if (keysym == 0xff52)
		mlx_data->map_data->angle_x -= 0.1;
	if (keysym == 0xff54)
		mlx_data->map_data->angle_x += 0.1;
	if (keysym == 0x0061)
		mlx_data->map_data->angle_z += 0.1;
	if (keysym == 0x0064)
		mlx_data->map_data->angle_z -= 0.1;
}

void	projection_menu(t_mlx_data *mlx_data)
{
	mlx_data->map_data->angle_x = 0;
	mlx_data->map_data->angle_y = 0;
	mlx_data->map_data->angle_z = 0;
	if (mlx_data->map_data->projection == 1)
	{
		mlx_data->map_data->angle_x = 1.57;
	}
	else if (mlx_data->map_data->projection == 2)
	{
		mlx_data->map_data->angle_y = 1.57;
	}
	else if (mlx_data->map_data->projection == 3)
		mlx_data->map_data->angle_z = 1.57;
	else
	{
		mlx_data->map_data->angle_x = 0;
		mlx_data->map_data->angle_y = 0;
		mlx_data->map_data->angle_z = 0;
	}
}

void	menu_key_handle(int keysym, t_mlx_data *mlx_data)
{
	if (keysym == 0x007a)
		mlx_data->keyboard.zoom = 1;
	if (keysym == 0x0074)
		mlx_data->keyboard.translation = 1;
	if (keysym == 0x0072)
		mlx_data->keyboard.rotate = 1;
	if (keysym == 0x0070)
	{
		mlx_data->map_data->projection += 1;
		if (mlx_data->map_data->projection == 5)
			mlx_data->map_data->projection = 1;
		projection_menu(mlx_data);
	}
}
