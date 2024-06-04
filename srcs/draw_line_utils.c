/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:44:17 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:50:24 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_image(t_img_data *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length + x
			* (img_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_safe_px_to_image(t_img_data *img_data, int x, int y, int color)
{
	if (x <= WIN_WIDTH && x > 0 && y >= 0 && y <= WIN_HEIGHT)
		put_pixel_to_image(img_data, x, y, color);
}

unsigned long	create_rgb(t_color_tra *color_tra, int i, int dP)
{
	int	r;
	int	b;
	int	g;
	int	z;

	if (dP != 0)
		z = (color_tra->beginz + (color_tra->endz - color_tra->beginz) * i
				/ dP);
	else
		z = color_tra->endz;
	r = 255;
	if (z == color_tra->lowest)
	{
		g = 255;
		b = 255;
	}
	else
	{
		g = 255 - (255 / (1 + abs(color_tra->highest - z)) * 2);
		b = 255 - (255 / (1 + abs(color_tra->highest - z)) * 2);
	}
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_point2	convert_isometric(int x3, int y3, int z3, t_map_data *map_data)
{
	int			tmp;
	t_point2	p2;

	x3 = x3 * cos(map_data->angle_y) + z3 * sin(map_data->angle_y);
	z3 = z3 * cos(map_data->angle_y) - x3 * sin(map_data->angle_y);
	tmp = x3;
	x3 = x3 * cos(map_data->angle_z) - y3 * sin(map_data->angle_z);
	y3 = tmp * sin(map_data->angle_z) + y3 * cos(map_data->angle_z);
	tmp = y3;
	y3 = y3 * cos(map_data->angle_x) - z3 * sin(map_data->angle_x);
	z3 = tmp * sin(map_data->angle_x) + z3 * cos(map_data->angle_x);
	if (map_data->projection == 0 || map_data->projection == 4)
	{
		p2.x = (x3 - y3) * cos(0.8);
		p2.y = (x3 + y3) * sin(0.8) - (z3);
	}
	else
	{
		p2.x = x3;
		p2.y = y3;
	}
	return (p2);
}

t_vector2	*convert_vector3_to_vector2(t_vector3 vector3, t_map_data *map_data,
		t_keyboard *kb)
{
	t_vector2	*vector2;

	vector2 = NULL;
	if (map_data == NULL)
		return (vector2);
	vector2 = malloc(sizeof(t_vector2));
	if (vector2 == NULL)
		return (NULL);
	convert_p_to_iso(vector2, vector3, map_data);
	if (kb->translation == 0)
	{
		map_data->x_offset = (WIN_WIDTH / 2) - ((((map_data->map_width / 2)
						- (map_data->map_height / 2)) * cos(0.8))
				* map_data->zoom_factor);
		map_data->y_offset = get_y_offset(map_data, map_data->zoom_factor);
	}
	vector2->beginx += map_data->x_offset;
	vector2->endx += map_data->x_offset;
	vector2->beginy += map_data->y_offset;
	vector2->endy += map_data->y_offset;
	return (vector2);
}
