/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2024/05/12 07:25:10 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_mlx(t_data *data)
{
	int		t;

	data->mlx = mlx_init();
	calculate_scale(data);
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
		return (ft_putstr("Not a valid file\n"), free(data), NULL);
	file = store_file(fd);
	parse_file(data, file);
	free(file);
	close(fd);
	return (data);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		start_visual(av[1]);
	else
		ft_putstr_fd("Error\nMust have only 2 arguments\n", 2);
	return (0);
}
