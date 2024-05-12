/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:12:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/12 07:25:16 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_scale(t_data *data)
{
	mlx_get_screen_size(data->mlx, &data->screen_x, &data->screen_y);
	data->scale = SCALE;
	while ((ft_abs(data->iso_x.end * data->scale)
			+ ft_abs(data->iso_x.start * data->scale)
			+ (2 * PADDING) > data->screen_x
			|| ft_abs(data->iso_y.end * data->scale)
			+ ft_abs(data->iso_y.start * data->scale)
			+ (2 * PADDING) > data->screen_y)
		&& data->scale > 1)
		data->scale--;
	data->iso_x.end *= data->scale;
	data->iso_x.start *= data->scale;
	data->iso_y.end *= data->scale;
	data->iso_y.start *= data->scale;
	data->win_x = ft_abs(data->iso_x.end)
		+ ft_abs(data->iso_x.start) + (2 * PADDING);
	data->win_y = ft_abs(data->iso_y.end)
		+ ft_abs(data->iso_y.start) + (2 * PADDING);
	data->win_x = ft_min(data->win_x, data->screen_x);
	data->win_y = ft_min(data->win_y, data->screen_y);
}

void	start_visual(char *file)
{
	t_data	*data;

	data = init_data(file);
	if (!data)
		return ;
	start_mlx(data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	destroy_map(data->map);
	free(data);
	exit(1);
}

void	calculate_visual(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (++x < data->max_x)
			draw_iso_point(data, x, y);
	}
}
