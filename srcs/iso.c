/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:49:06 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/07 09:23:25 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	iso_x(double x, double y)
{
	return (x - y);
}

double	iso_y(double x, double y, double z)
{
	return ((x + y) / 2 - z);
}

void	unscale_point(t_point *p, double scale)
{
	p->x /= scale;
	p->y /= scale;
}

void	scale_point(t_point *p, double scale)
{
	p->x *= scale;
	p->y *= scale;
}
	