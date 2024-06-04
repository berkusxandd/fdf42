/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 17:47:03 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_mlx_data *mlx_data)
{
	int	i;
	int	j;

	i = 0;
	if (mlx_data->map_data != NULL)
	{
		if (mlx_data->map_data->map != NULL)
		{
			while (mlx_data->map_data->map[i])
			{
				j = 0;
				while (mlx_data->map_data->map[i][j])
				{
					free(mlx_data->map_data->map[i][j]);
					j++;
				}
				free(mlx_data->map_data->map[i]);
				i++;
			}
			free(mlx_data->map_data->map);
		}
	}
	free(mlx_data->map_data);
}
