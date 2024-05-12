/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:50:34 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/12 07:30:04 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	color(int r, int g, int b)
{
	t_pixel	dest;

	dest.r = r;
	dest.g = g;
	dest.b = b;
	dest.a = 1;
	return (dest);
}

void	draw_point(t_data *data, int x, int y, t_pixel color)
{
	x += ft_abs(data->iso_x.start) + PADDING;
	y += ft_abs(data->iso_y.start) + PADDING;
	if (y < 0 || x < 0 || y >= data->win_y
		|| x >= data->win_x)
		return ;
	data->draw[data->win_x * y + x] = color;
}

t_pixel	calculate_color(t_data *data, t_point p, double red)
{
	t_pixel	dest;

	p.x += ft_abs(data->iso_x.start) + PADDING;
	p.y += ft_abs(data->iso_y.start) + PADDING;
	dest.a = 1;
	dest.g = ft_map(range(0, data->win_x), range(0, 255), p.x);
	dest.b = ft_map(range(0, data->win_y), range(0, 255), p.y);
	dest.r = red;
	return (dest);
}

void	draw_line(t_data *data, t_point a, t_point b, t_point h)
{
	int			i;
	t_point		d;
	double		steps;
	t_pixel		pixel;

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	steps = ft_max(ft_abs(d.x), ft_abs(d.y));
	d.x /= steps;
	d.y /= steps;
	i = -1;
	while (++i <= steps)
	{
		pixel = calculate_color(data, a, ft_map(range(0, data->max_z),
					range(0, 255), h.x + (i / steps) * (h.y - h.x)));
		draw_point(data, a.x, a.y, pixel);
		a.x = a.x + d.x;
		a.y = a.y + d.y;
	}
}

void	draw_iso_point(t_data *data, int x, int y)
{
	t_point	origin;
	t_point	other;
	t_point	h;

	origin.x = iso_x(x, y);
	origin.y = iso_y(x, y, data->map[y][x]);
	scale_point(&origin, data->scale);
	if (x < data->max_x - 1)
	{
		other.x = iso_x(x + 1, y);
		other.y = iso_y(x + 1, y, data->map[y][x + 1]);
		h.x = data->map[y][x];
		h.y = data->map[y][x + 1];
		scale_point(&other, data->scale);
		draw_line(data, origin, other, h);
	}
	if (y < data->max_y - 1)
	{
		other.x = iso_x(x, y + 1);
		other.y = iso_y(x, y + 1, data->map[y + 1][x]);
		h.x = data->map[y][x];
		h.y = data->map[y + 1][x];
		scale_point(&other, data->scale);
		draw_line(data, origin, other, h);
	}
}
