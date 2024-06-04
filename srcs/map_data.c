/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:28 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 17:47:29 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	find_highest(char ***map)
{
	int	highest;
	int	i;
	int	j;

	highest = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (ft_atoi(map[i][j]) > highest)
			{
				highest = ft_atoi(map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (highest);
}

int	find_lowest(char ***map)
{
	int	lowest;
	int	i;
	int	j;

	lowest = 1;
	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (ft_atoi(map[i][j]) < lowest)
			{
				lowest = ft_atoi(map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (lowest);
}
