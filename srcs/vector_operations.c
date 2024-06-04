/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:48:09 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:51:21 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	convert_p_to_iso(t_vector2 *vector2, t_vector3 vector3,
		t_map_data *map_data)
{
	t_point2	iso_p;

	iso_p = convert_isometric(vector3.beginx, vector3.beginy, vector3.beginz,
			map_data);
	vector2->beginx = iso_p.x;
	vector2->beginy = iso_p.y;
	iso_p = convert_isometric(vector3.endx, vector3.endy, vector3.endz,
			map_data);
	vector2->endx = iso_p.x;
	vector2->endy = iso_p.y;
}

t_vector3	horizontal_vector3(int i, int j, t_map_data *map_data)
{
	t_vector3	h_vector3;

	h_vector3.beginx = j * map_data->zoom_factor;
	h_vector3.beginy = i * map_data->zoom_factor;
	h_vector3.endx = h_vector3.beginx + map_data->zoom_factor;
	h_vector3.endy = h_vector3.beginy;
	h_vector3.beginz = (ft_atoi(map_data->map[i][j]) - map_data->lowest)
		* map_data->zoom_factor * 0.1;
	h_vector3.endz = (ft_atoi(map_data->map[i][j + 1]) - map_data->lowest)
		* map_data->zoom_factor * 0.1;
	return (h_vector3);
}

t_vector3	vertical_vector(int i, int j, t_map_data *map_data)
{
	t_vector3	v_vector3;

	v_vector3.beginx = j * map_data->zoom_factor;
	v_vector3.beginy = i * map_data->zoom_factor;
	v_vector3.endx = v_vector3.beginx;
	v_vector3.endy = v_vector3.beginy + map_data->zoom_factor;
	v_vector3.beginz = (ft_atoi(map_data->map[i][j]) - map_data->lowest)
		* map_data->zoom_factor * 0.1;
	v_vector3.endz = (ft_atoi(map_data->map[i + 1][j]) - map_data->lowest)
		* map_data->zoom_factor * 0.1;
	return (v_vector3);
}

int	create_vectors(t_mlx_data *mlx_data, int i, int j, t_keyboard *kb)
{
	t_vector3	h_vector3;
	t_vector3	v_vector3;
	t_color_tra	color_tra;

	while (mlx_data->map_data->map[i][j])
	{
		if (mlx_data->map_data->map[i][j + 1] != NULL)
		{
			h_vector3 = horizontal_vector3(i, j, mlx_data->map_data);
			color_tra.beginz = ft_atoi(mlx_data->map_data->map[i][j]);
			color_tra.endz = ft_atoi(mlx_data->map_data->map[i][j + 1]);
			if (draw_line(mlx_data, h_vector3, &color_tra, kb) == -1)
				return (-1);
		}
		if (mlx_data->map_data->map[i + 1] != NULL)
		{
			v_vector3 = vertical_vector(i, j, mlx_data->map_data);
			color_tra.beginz = ft_atoi(mlx_data->map_data->map[i][j]);
			color_tra.endz = ft_atoi(mlx_data->map_data->map[i + 1][j]);
			if (draw_line(mlx_data, v_vector3, &color_tra, kb) == -1)
				return (-1);
		}
		j++;
	}
	return (1);
}
