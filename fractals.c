/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:03 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/04 12:40:47 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	mandelbrot(t_fractol *f, size_t ix, size_t iy, double aspect_ratio)
{
	t_complex	c;
	t_complex	z;
	size_t		i;

	c = (t_complex){
		.re = aspect_ratio * ((double)(4 * ix) / f->img->width - 2),
		.im = (double)(4 * iy) / f->img->width - 2.
	};
	c.re = c.re * f->zoom + f->zoom_x;
	c.im = c.im * f->zoom + f->zoom_y;
	z = (t_complex){0};
	i = 0;
	while (i < f->max_iterations && z.re * z.re + z.im * z.im < 4.)
	{
		z = c_add(c_sqr(z), c);
		++i;
	}
	return (i);
}

uint32_t	julia(t_fractol *f, size_t ix, size_t iy, double aspect_ratio)
{
	t_complex	c;
	t_complex	z;
	size_t		i;

	z = (t_complex){
		.re = aspect_ratio * ((double)(4 * ix) / f->img->width - 2.),
		.im = (double)(4 * iy) / f->img->width - 2.
	};
	z.re = z.re * f->zoom + f->zoom_x;
	z.im = z.im * f->zoom + f->zoom_y;
	c = f->julia_c;
	i = 0;
	while (i < f->max_iterations && z.re * z.re + z.im * z.im < 4.)
	{
		z = c_add(c_sqr(z), c);
		++i;
	}
	return (i);
}

uint32_t	prinssi(t_fractol *f, size_t ix, size_t iy, double aspect_ratio)
{
	t_complex	c;
	t_complex	z;
	size_t		i;

	c = (t_complex){
		.re = aspect_ratio * ((double)(4 * ix) / f->img->width - 2.),
		.im = (double)(4 * iy) / f->img->width - 2.
	};
	c.re = c.re * f->zoom + f->zoom_x;
	c.im = c.im * f->zoom + f->zoom_y;
	z = (t_complex){0};
	i = 0;
	while (i < f->max_iterations && z.re * z.re + z.im * z.im < 4.)
	{
		z = c_div(c_add(c_sqr(z), c), c_sub(c_sqr(z), c));
		++i;
	}
	return (i);
}
