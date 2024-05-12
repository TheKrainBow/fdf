/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:47:56 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/12 07:32:45 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	data_default_values(t_data *data)
{
	data->max_x = INT_MIN;
	data->max_y = INT_MIN;
	data->max_z = INT_MIN;
	data->iso_x.start = INT_MAX;
	data->iso_x.end = INT_MIN;
	data->iso_y.start = INT_MAX;
	data->iso_y.end = INT_MIN;
}

int	parse_line(t_data *data, int **map, char *line, int idx)
{
	char	**tab;
	int		i;

	tab = ft_split(line, ' ');
	if (idx == 0)
		data->max_x = ft_tablen(tab);
	else if (data->max_x != ft_tablen(tab))
	{
		ft_putstr_fd("Error in parsing: lines doesn't have the same size\n", 2);
		ft_free_tab(tab);
		return (0);
	}
	*map = ft_calloc(sizeof(int), data->max_x);
	i = -1;
	while (tab[++i])
	{
		(*map)[i] = ft_atoi(tab[i]);
		data->max_z = ft_max(data->max_z, (*map)[i]);
		data->iso_x.start = ft_min(data->iso_x.start, iso_x(i, idx));
		data->iso_x.end = ft_max(data->iso_x.end, iso_x(i, idx));
		data->iso_y.start = ft_min(data->iso_y.start, iso_y(i, idx, (*map)[i]));
		data->iso_y.end = ft_max(data->iso_y.end, iso_y(i, idx, (*map)[i]));
	}
	ft_free_tab(tab);
	return (1);
}

void	parse_file(t_data *data, char *file)
{
	char	**lines;
	int		i;

	data_default_values(data);
	lines = ft_split(file, '\n');
	data->max_y = ft_tablen(lines);
	data->map = ft_calloc(sizeof(int *), data->max_y + 1);
	i = -1;
	while (lines[++i])
	{
		if (parse_line(data, data->map + i, lines[i], i) == 0)
		{
			destroy_map(data->map);
			break ;
		}
	}
	ft_free_tab(lines);
}

void	destroy_map(int **map)
{
	int	i;

	i = -1;
	while (map && map[++i])
		free(map[i]);
	free(map);
}
