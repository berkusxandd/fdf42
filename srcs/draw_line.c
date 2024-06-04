/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:26 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:47:44 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	sign_modifier(int dX, int dY, int *signx, int *signy)
{
	if (dX < 0)
		*signx = -1;
	else
		*signx = 1;
	if (dY < 0)
		*signy = -1;
	else
		*signy = 1;
}

void	slope_more_1(t_img_data *img, t_vector2 *v2, t_point2 dp,
		t_color_tra *color)
{
	int			p;
	t_point2	p2;
	int			i;
	int			signx;
	int			signy;

	i = -1;
	p2.x = v2->beginx;
	p2.y = v2->beginy;
	sign_modifier(dp.x, dp.y, &signx, &signy);
	put_safe_px_to_image(img, p2.x, p2.y, create_rgb(color, 0, abs(dp.y)));
	p = 2 * abs(dp.x) - abs(dp.y);
	while (++i < abs(dp.y))
	{
		p2.y += signy;
		if (p < 0)
			p += 2 * abs(dp.x);
		else
		{
			p += 2 * abs(dp.x) - 2 * abs(dp.y);
			p2.x += signx;
		}
		put_safe_px_to_image(img, p2.x, p2.y, create_rgb(color, i, abs(dp.y)));
	}
}

int	draw_map(t_mlx_data *mlx_data, t_keyboard *kb)
{
	int	i;
	int	j;

	i = 0;
	while (mlx_data->map_data->map[i])
	{
		j = 0;
		if (create_vectors(mlx_data, i, j, kb) == -1)
			return (-1);
		i++;
	}
	return (1);
}

void	slope_less_1(t_img_data *img, t_vector2 *v2, t_point2 dp,
		t_color_tra *color)
{
	int			p;
	t_point2	p2;
	int			i;
	int			signx;
	int			signy;

	i = -1;
	p2.x = v2->beginx;
	p2.y = v2->beginy;
	sign_modifier(dp.x, dp.y, &signx, &signy);
	put_safe_px_to_image(img, p2.x, p2.y, create_rgb(color, 0, abs(dp.x)));
	p = 2 * abs(dp.y) - abs(dp.x);
	while (++i < abs(dp.x))
	{
		p2.x += signx;
		if (p < 0)
			p += 2 * abs(dp.y);
		else
		{
			p2.y += signy;
			p += 2 * abs(dp.y) - 2 * abs(dp.x);
		}
		put_safe_px_to_image(img, p2.x, p2.y, create_rgb(color, i, abs(dp.x)));
	}
}

int	draw_line(t_mlx_data *mlx_data, t_vector3 vector3, t_color_tra *color_tra,
		t_keyboard *kb)
{
	t_point2	dp;
	t_vector2	*vector2;

	vector2 = convert_vector3_to_vector2(vector3, mlx_data->map_data, kb);
	if (vector2 == NULL)
		return (-1);
	dp.x = vector2->endx - vector2->beginx;
	dp.y = vector2->endy - vector2->beginy;
	color_tra->highest = mlx_data->map_data->highest;
	color_tra->lowest = mlx_data->map_data->lowest;
	if (abs(dp.x) > abs(dp.y))
		slope_less_1(mlx_data->img_data, vector2, dp, color_tra);
	else
		slope_more_1(mlx_data->img_data, vector2, dp, color_tra);
	free(vector2);
	return (1);
}
