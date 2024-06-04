/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:52 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 17:47:53 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_height(char *map_name, t_map_data *map_data)
{
	int		i;
	char	*line;
	int		fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		error_check_before_map(fd, map_data, MAP_ERROR_YAXIS_ERROR);
	line = get_next_line(fd);
	if (line == NULL)
		error_check_before_map(fd, map_data, MAP_ERROR_YAXIS_ERROR);
	i = 0;
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

int	map_width_check(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	check_map(char ***map, int x_a, int y_a)
{
	int	i;

	i = 0;
	if (y_a < 2 || x_a < 2)
		return (0);
	while (map[i])
	{
		if (map_width_check(map[i]) != x_a)
			return (0);
		i++;
	}
	return (1);
}

int	fill_map(t_map_data *map_data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line)
	{
		map_data->map[i] = ft_split(line, ' ');
		if (map_data->map[i] == NULL)
		{
			free(line);
			free_get_next_line_res(fd);
			close(fd);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	map_data->map[i] = NULL;
	return (1);
}

int	map_parse(char *map_name, t_map_data *map_data)
{
	char	*line;
	int		fd;
	int		y_a;
	int		x_a;

	fd = open(map_name, O_RDONLY, 0666);
	if (fd == -1)
		error_check_before_map(fd, map_data, MAP_ERROR_MAP_FILE_ERROR);
	y_a = map_height(map_name, map_data);
	map_data->map = malloc(sizeof(char ***) * (y_a + 1));
	if (map_data->map == NULL)
		error_check_before_map(fd, map_data, MAP_ERROR_MEMORY_ERROR);
	line = get_next_line(fd);
	if (line == NULL)
		error_check_after_map(fd, map_data, line, 5);
	x_a = map_width_generate(line);
	if (x_a == -1)
		error_check_after_map(fd, map_data, line, 6);
	if (fill_map(map_data, line, fd) == -1)
		return (-1);
	map_data_write(map_data, x_a, y_a);
	if (check_map(map_data->map, x_a, y_a) == 0)
		return (-2);
	close(fd);
	return (1);
}
