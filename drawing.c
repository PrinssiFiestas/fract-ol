/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:02 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/05 09:44:44 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_pixel(t_fractol *f, t_fractal fractal, double aspect, size_t i)
{
	size_t	ic;

	ic = f->iters[i];
	if (!f->valid_pixel[i & (sizeof f->valid_pixel - 1)]
		&& (i & (sizeof f->valid_pixel - 1)) == f->valid_pixel_i)
	{
		ic = fractal(f, i % f->img->width, i / f->img->height, aspect);
		if (ic == f->max_iterations)
			ic = 0;
		f->iters[i] = ic;
	}
	if (ic != 0)
	{
		ic = PALETTE_LENGTH - 1 - ic * PALETTE_LENGTH / f->max_iterations;
		ic += (size_t)(100 * mlx_get_time());
		ic &= PALETTE_LENGTH - 1;
	}
	ft_memcpy(f->img->pixels + 4 * i, &f->palette[ic], 4);
}

static void	draw_frame(t_fractol *f, t_fractal fractal)
{
	size_t		i;
	double		aspect_ratio;

	aspect_ratio = (double)f->img->width / f->img->height;
	i = 0;
	while (i < f->img->width * f->img->height)
	{
		draw_pixel(f, fractal, aspect_ratio, i);
		++i;
	}
	f->valid_pixel[f->valid_pixel_i] = true;
	f->valid_pixel_i = (f->valid_pixel_i + 1) & (sizeof f->valid_pixel - 1);
	assert_mlx(f, mlx_image_to_window(f->mlx, f->img, 0, 0) != -1);
}

void	draw_mandelbrot(void *fractol)
{
	draw_frame(fractol, mandelbrot);
}

void	draw_julia(void *fractol)
{
	draw_frame(fractol, julia);
}

void	draw_prinssi(void *fractol)
{
	draw_frame(fractol, prinssi);
}
