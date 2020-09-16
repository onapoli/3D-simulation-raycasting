/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 18:21:18 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/11 13:51:44 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct	s_bmp_file_header
{
	u_int16_t	signature;
	u_int32_t	file_size;
	u_int16_t	reserved_1;
	u_int16_t	reserved_2;
	u_int32_t	offset;
}				t_bmp_file_header;

typedef	struct	s_bmp_info_header
{
	u_int32_t	info_header_size;
	int32_t		image_width;
	int32_t		image_height;
	u_int16_t	color_planes;
	u_int16_t	bpp;
	u_int32_t	compression;
	u_int32_t	image_size;
	int32_t		x_pixels_per_meter;
	int32_t		y_pixels_per_meter;
	u_int32_t	colors_used;
	u_int32_t	important_colors;
}				t_bmp_info_header;

typedef struct	s_ray
{
	double	angle;
	double	wall_distance;
	int		wall_pixels;
	int		wall_intersect;
	double	wall_pos;
}				t_ray;

typedef struct	s_sprite_data
{
	int				x_pos;
	int				y_pos;
	double			angle;
	double			distance;
	int				show;
}				t_sprite_data;

typedef struct	s_sprite
{
	t_sprite_data	data;
	struct s_sprite	*next;
}				t_sprite;

typedef struct	s_texture
{
	char		*path;
	void		*texture;
	char		*texture_data;
	int			tex_width;
	int			tex_height;
	int			tex_bpp;
	int			tex_size_line;
	int			tex_endian;
}				t_texture;

typedef struct	s_player
{
	double		x_pos;
	double		y_pos;
	double		angle;
}				t_player;

typedef struct	s_level
{
	int				cell_length;
	int				wall_height;
	char			**map;
	t_sprite		*sprites;
	unsigned long	ceiling_color;
	unsigned long	floor_color;
}				t_level;

typedef struct	s_file_data
{
	int			r;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			s;
	int			f;
	int			c;
}				t_file_data;

typedef struct	s_session
{
	void		*mlx;
	void		*window;
	void		*image;
	char		*image_data;
	int			image_bpp;
	int			image_size_line;
	int			image_endian;
	int			win_width;
	int			win_height;
	double		fov;
	double		projection_distance;
	t_level		level;
	t_player	player;
	t_texture	textures[4];
	t_texture	sprite_texture;
	double		time;
	int			lastkey;
	int			win_minimized;
	t_file_data	file_data;
}				t_session;

typedef struct	s_sprite_view
{
	int	x_midpoint;
	int	pixel_width;
	int	pixel_height;
}				t_sprite_view;

typedef struct	s_wall_draw
{
	t_texture	texture_src;
	char		texture[4];
	double		texture_increment;
	int			final_wall_pixels;
	double		i_tex;
	double		j_tex;
	int			start_j;
	int			j;
	int			final_j;
}				t_wall_draw;

typedef	struct	s_sprite_draw
{
	int		x_init;
	int		x_finish;
	double	width_texture_increment;
	double	height_texture_increment;
	int		final_height;
	int		i;
	int		j;
	double	i_tex;
	double	j_tex;
	int		j_start;
	int		j_finish;
	double	j_tex_start;
	char	texture[4];
}				t_sprite_draw;

int				minimize(void *param);
int				maximize(t_session *session);
int				load_wall_textures(t_session *session);
void			launch_hooks_n_loops(t_session *session);
int				timer(void *param);
void			time_update(int keycode, t_session *session);
void			free_textures(t_session *session);
int				start_raycasting(t_session *session, double *z_buffer);
void			ft_adjust_window_size(t_session *session);
void			handle_window_creation(int argc, char **argv,
t_session *session);
void			create_session_image(t_session *session);
int				free_sprites(t_sprite **sprites);
int				free_map(char **map);
int				ft_strcmp(char *str_1, char *str_2);
void			set_default_level_values(t_session *session);
void			check_minimum_args(int argc);
double			deg_2_rad(int degrees);
double			normalize_angle(double angle);
double			get_2_point_distance(double x1, double y1, double x2,
double y2);
int				get_direction(double angle, char target);
int				get_wall_pixels(int wall_height, double wall_distance,
double projection_plane_distance);
int				move(t_session *session, int keycode);
int				rotate(t_session *session, int keycode);
int				get_cell(size_t cell[2], double x_coord, double y_coord,
int cell_length);
int				check_wall(char **map, size_t row, size_t column);
int				raycaster(t_session *session, double *z_buffer);
int				vertical_wall(double intersect_coord[2], double angle,
size_t cell_column, t_session *session);
int				horizontal_wall(double intersect_coord[2], double angle,
size_t cell_row, t_session *session);
double			get_horizontal_intersection(double slope, double y_intersect,
double x_pos, double y_pos);
double			get_vertical_intersection(double slope, double x_intersect,
double x_pos, double y_pos);
double			get_axis_parallel(int cell_length, int cell_position, int dir);
int				project_sprites(t_session *session, double *z_buffer);
int				get_sprite_visibility(double sprite_angle, double player_angle,
double fov);
double			get_sprite_angle(double s_x_pos, double s_y_pos, double p_x_pos,
double p_y_pos);
int				sprite_screen_midpoint(double player_angle, double sprite_angle,
double fov, int win_width);
int				draw_wall_texture(t_session *session, int x, t_ray *ray);
int				draw_sprites(t_sprite_data *sprites, t_session *session,
double *z_buffer);
int				draw_pixel(t_session *session, int x, int y,
unsigned long color);
int				draw_texture(t_session *session, int x, int y, char texture[4]);
int				get_texture(t_texture texture_src, int x, int y,
char texture[4]);
int				draw_single_sprite(t_session *session,
t_sprite_view *sprite_view, double distance, double *z_buffer);
int				create_bmp(int img_width, int img_height, int img_bpp,
char *img_data);
#endif
