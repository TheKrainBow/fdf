/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2024/05/07 09:24:09 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	start_mlx(t_data *data)
{
	int		t;

	data->iso_x.end *= SCALE;
	data->iso_x.start *= SCALE;
	data->iso_y.end *= SCALE;
	data->iso_y.start *= SCALE;
	data->win_x = ft_abs(data->iso_x.end)
		+ ft_abs(data->iso_x.start) + (2 * PADDING);
	data->win_y = (iso_y(data->max_x, data->max_y, 0)
			* (SCALE - 1)) - iso_y(0, 0, 0)
		* (SCALE - 1) + (PADDING * 2) + (data->max_z * (SCALE - 1));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "FdF");
	data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->draw = (t_pixel *)mlx_get_data_addr(data->img, &t, &t, &t);
	data->img2 = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->draw2 = (t_pixel *)mlx_get_data_addr(data->img2, &t, &t, &t);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keydown, data);
	calculate_visual(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

t_data	*init_data(char *str)
{
	int		fd;
	t_data	*data;
	char	*file;

	data = malloc(sizeof(t_data));
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (NULL);
	file = store_file(fd);
	parse_file(data, file);
	free(file);
	close(fd);
	return (data);
}

void	start_visual(char *file)
{
	t_data	*data;

	data = init_data(file);
	start_mlx(data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	destroy_map(data->map);
	free(data);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		start_visual(av[1]);
	else
		ft_putstr_fd("Error\nMust have only 2 arguments\n", 2);
	return (0);
}
