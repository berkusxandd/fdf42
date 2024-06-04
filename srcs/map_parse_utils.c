/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:33 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:46:06 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_data_down_boundary(t_map_data *map_data)
{
	int	i;
	int	j;
	int	lowest;
	int	lowest_i;
	int	lowest_j;

	lowest = 2147483647;
	i = -1;
	while (map_data->map[++i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (ft_atoi(map_data->map[i][j]) < lowest)
			{
				lowest = ft_atoi(map_data->map[i][j]);
				lowest_i = i;
				lowest_j = j;
			}
			j++;
		}
	}
	map_data->lowest = lowest;
	map_data->lowest_i = lowest_i;
	map_data->lowest_j = lowest_j;
}

void	map_data_upper_boundary(t_map_data *map_data)
{
	int	i;
	int	j;
	int	highest;
	int	highest_i;
	int	highest_j;

	highest = -2147483648;
	i = -1;
	while (map_data->map[++i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (ft_atoi(map_data->map[i][j]) > highest)
			{
				highest = ft_atoi(map_data->map[i][j]);
				highest_i = i;
				highest_j = j;
			}
			j++;
		}
	}
	map_data->highest = highest;
	map_data->highest_i = highest_i;
	map_data->highest_j = highest_j;
}

int	map_width_generate(char *line)
{
	int		i;
	char	**line_split;

	if (line)
		sleep(0);
	line_split = ft_split(line, ' ');
	if (line_split == NULL)
		return (-1);
	i = 0;
	while (line_split[i])
		i++;
	i = 0;
	while (line_split[i])
	{
		free(line_split[i]);
		i++;
	}
	free(line_split);
	return (i);
}

int	lowest_y_calc(t_map_data *map_data)
{
	int	zoom_factor;
	int	y_offset;
	int	lowest_y;

	if (map_data->map_width > map_data->map_height)
		zoom_factor = (2 * WIN_WIDTH) / (3 * map_data->map_width);
	else
		zoom_factor = (2 * WIN_HEIGHT) / (3 * map_data->map_height);
	y_offset = get_y_offset(map_data, zoom_factor);
	lowest_y = get_lowest_y(map_data, zoom_factor);
	lowest_y += y_offset;
	if (lowest_y > WIN_HEIGHT)
	{
		while ((get_lowest_y(map_data, zoom_factor) + y_offset > WIN_HEIGHT))
		{
			zoom_factor--;
			y_offset = get_y_offset(map_data, zoom_factor);
		}
	}
	return (zoom_factor);
}

int	zoom_factor_calc(t_map_data *map_data)
{
	int	zoom_factor;
	int	y_offset;
	int	highest_y;

	if (map_data->start == 0)
	{
		zoom_factor = lowest_y_calc(map_data);
		y_offset = get_y_offset(map_data, zoom_factor);
		highest_y = get_highest_y(map_data, zoom_factor);
		highest_y += y_offset;
		if (highest_y < 0)
		{
			while (get_highest_y(map_data, zoom_factor) + y_offset < 0)
			{
				zoom_factor--;
				y_offset = get_y_offset(map_data, zoom_factor);
			}
		}
		return (zoom_factor);
	}
	return (map_data->zoom_factor);
}
