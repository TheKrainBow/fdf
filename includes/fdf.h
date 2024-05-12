/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:23:10 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/12 07:31:54 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <limits.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

# define KEY_ESC 65307
# define SCALE 20
# define PADDING 50

typedef struct s_pixel
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}				t_pixel;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_data
{
	int			**map;
	int			max_x;
	int			max_y;
	int			max_z;
	int			scale;
	int			padding;
	t_range		iso_x;
	t_range		iso_y;

	void		*mlx;

	int			screen_x;
	int			screen_y;

	void		*win;
	int			win_x;
	int			win_y;

	void		*img;
	t_pixel		*draw;

	void		*img2;
	t_pixel		*draw2;
}				t_data;

int		hook_keydown(int key_code, void *param);

void	parse_file(t_data *data, char *file);
void	destroy_map(int **map);
int		parse_line(t_data *data, int **map, char *line, int idx);

double	iso_x(double x, double y);
double	iso_y(double x, double y, double z);
void	unscale_point(t_point *p, double scale);
void	scale_point(t_point *p, double scale);

t_pixel	color(int r, int g, int b);
void	draw_point(t_data *data, int x, int y, t_pixel color);
t_pixel	calculate_color(t_data *data, t_point p, double red);
void	draw_line(t_data *data, t_point a, t_point b, t_point h);
void	draw_iso_point(t_data *data, int x, int y);

void	calculate_visual(t_data *data);
void	calculate_scale(t_data *data);
void	start_visual(char *file);
t_data	*init_data(char *str);
void	start_mlx(t_data *data);

#endif