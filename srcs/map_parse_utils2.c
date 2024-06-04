/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:45 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:49:35 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_y_offset(t_map_data *map_data, int zoom_factor)
{
	return ((WIN_HEIGHT / 2) - ((((map_data->map_height / 2)
					+ (map_data->map_width / 2)) * sin(0.8) - (0 * zoom_factor
					* 0.1)) * zoom_factor));
}

int	get_lowest_y(t_map_data *map_data, int zoom_factor)
{
	return (((map_data->lowest_j + map_data->lowest_i) * zoom_factor) * sin(0.8)
		- ((ft_atoi(map_data->map[map_data->lowest_i][map_data->lowest_j])
			- map_data->lowest) * zoom_factor * 0.1));
}

int	get_highest_y(t_map_data *map_data, int zoom_factor)
{
	return (((map_data->highest_j + map_data->highest_i) * zoom_factor)
		* sin(0.8)
		- ((ft_atoi(map_data->map[map_data->highest_i][map_data->highest_j])
			- map_data->lowest) * zoom_factor * 0.1));
}

void	map_data_write(t_map_data *map_data, int x_a, int y_a)
{
	map_data->map_width = x_a;
	map_data->map_height = y_a;
	map_data_upper_boundary(map_data);
	map_data_down_boundary(map_data);
}
