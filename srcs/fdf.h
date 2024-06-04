/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:53 by bince             #+#    #+#             */
/*   Updated: 2024/06/04 20:47:29 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define MAP_ERROR_MAP_1_CHAR 1
# define MAP_ERROR_MAP_NOT_RECT 0
# define MAP_ERROR_MAP_FILE_ERROR 2
# define MAP_ERROR_YAXIS_ERROR 3
# define MAP_ERROR_MEMORY_ERROR 4
# include "../Libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct s_vector3
{
	int			beginx;
	int			beginy;
	int			beginz;
	int			endx;
	int			endy;
	int			endz;
}				t_vector3;

typedef struct s_vector2
{
	int			beginx;
	int			beginy;
	int			endx;
	int			endy;
}				t_vector2;

typedef struct s_color_tra
{
	int			beginz;
	int			endz;
	int			lowest;
	int			highest;
}				t_color_tra;

typedef struct s_map_data
{
	int			map_width;
	int			map_height;
	int			zoom_factor;
	int			highest;
	int			lowest;
	int			highest_i;
	int			highest_j;
	int			lowest_i;
	int			lowest_j;
	int			x_offset;
	int			y_offset;
	char		***map;
	int			start;
	float		angle_z;
	float		angle_x;
	float		angle_y;
	int			projection;
}				t_map_data;

typedef struct s_keyboard
{
	int			zoom;
	int			rotate;
	int			translation;
}				t_keyboard;

typedef struct s_fdf
{
	int			win_height;
	int			win_width;
}				t_fdf;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	t_map_data	*map_data;
	t_img_data	*img_data;
	t_keyboard	keyboard;
}				t_mlx_data;

typedef struct s_point2
{
	int			x;
	int			y;
}				t_point2;

void			put_pixel_to_image(t_img_data *img_data, int x, int y,
					int color);
int				map_parse(char *map_name, t_map_data *map_data);
int				draw_line(t_mlx_data *mlx_data, t_vector3 vector3,
					t_color_tra *color_tra, t_keyboard *kb);
int				zoom_factor_calc(t_map_data *map_data);
void			free_map(t_mlx_data *mlx_data);
int				get_y_offset(t_map_data *map_data, int zoom_factor);
void			param_error(int ac, char **env);
void			free_get_next_line_res(int fd);
void			error_check_before_map(int fd, t_map_data *map_data,
					int error_code);
void			error_check_after_map(int fd, t_map_data *map_data, char *line,
					int error_code);
void			map_data_down_boundary(t_map_data *map_data);
void			map_data_upper_boundary(t_map_data *map_data);
int				map_width_generate(char *line);
int				get_y_offset(t_map_data *map_data, int zoom_factor);
int				get_lowest_y(t_map_data *map_data, int zoom_factor);
int				get_highest_y(t_map_data *map_data, int zoom_factor);
void			map_data_write(t_map_data *map_data, int x_a, int y_a);
void			put_safe_px_to_image(t_img_data *img_data, int x, int y,
					int color);
unsigned long	create_rgb(t_color_tra *color_tra, int i, int dP);
t_point2		convert_isometric(int x3, int y3, int z3, t_map_data *map_data);
t_vector2		*convert_vector3_to_vector2(t_vector3 vector3,
					t_map_data *map_data, t_keyboard *kb);
t_vector3		horizontal_vector3(int i, int j, t_map_data *map_data);
t_vector3		vertical_vector(int i, int j, t_map_data *map_data);
int				create_vectors(t_mlx_data *mlx_data, int i, int j,
					t_keyboard *kb);
void			zoom_menu(int keysym, t_mlx_data *mlx_data);
void			translation_menu(int keysym, t_mlx_data *mlx_data);
void			rotation_menu(int keysym, t_mlx_data *mlx_data);
void			projection_menu(t_mlx_data *mlx_data);
void			menu_key_handle(int keysym, t_mlx_data *mlx_data);
int				draw_map(t_mlx_data *mlx_data, t_keyboard *kb);
int				find_lowest(char ***map);
int				find_highest(char ***map);
void			mlx_memory_error(t_mlx_data *mlx_data);
void			put_pixel_to_image(t_img_data *img_data, int x, int y,
					int color);
void			destroy_mlx(t_mlx_data *mlx_data);
int				handle_input(int keysym, t_mlx_data *mlx_data);
void			mlx_image_data_write(t_mlx_data *mlx_data);
void			mlx_data_write(t_mlx_data *mlx_data);
void			update_image(t_mlx_data *mlx_data);
void			keyboard_init(t_keyboard *kb);
void			convert_p_to_iso(t_vector2 *vector2, t_vector3 vector3,
					t_map_data *map_data);
#endif
