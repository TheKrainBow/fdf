/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:59:13 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/07 07:56:47 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_range	range(double a, double b)
{
	t_range	dest;

	dest.start = a;
	dest.end = b;
	return (dest);
}

double	ft_map(t_range input, t_range output, double value)
{
	double slope = 1.0 * (output.end - output.start) / (input.end - input.start);
	double tmp = output.start + slope * (value - input.start);
	//printf("[%.2f;%.2f] => [%.2f;%.2f];;%.2f => %.2f\n", input.start, input.end, output.start, output.end, value, tmp);
	return (tmp);
}