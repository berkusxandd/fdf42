/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:40 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:45:04 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	param_error(int ac, char **env)
{
	if (ac != 2 || env == NULL)
	{
		if (ac != 2)
			ft_putstr_fd("only one argument allowed (one map)\n", 2);
		if (env == NULL)
			ft_putstr_fd("no env is found\n", 2);
		exit(-1);
	}
}

void	free_get_next_line_res(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	error_check_before_map(int fd, t_map_data *map_data, int error_code)
{
	free(map_data);
	if (fd != -1)
		close(fd);
	if (error_code == MAP_ERROR_MAP_FILE_ERROR)
		ft_putstr_fd("map file error\n", 2);
	else
		ft_putstr_fd("memory error\n", 2);
	exit(-1);
}

void	error_check_after_map(int fd, t_map_data *map_data, char *line,
		int error_code)
{
	free(map_data->map);
	free(map_data);
	if (error_code > 5)
	{
		free(line);
		free_get_next_line_res(fd);
	}
	close(fd);
	ft_putstr_fd("memory error\n", 2);
	exit(-1);
}

void	mlx_memory_error(t_mlx_data *mlx_data)
{
	ft_putstr_fd("memory error\n", 2);
	destroy_mlx(mlx_data);
}
