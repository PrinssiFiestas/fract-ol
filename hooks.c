/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:31 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/04 19:11:11 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook(mlx_key_data_t key, void *_f)
{
	t_fractol	*f;

	f = _f;
	if (key.key == MLX_KEY_ESCAPE)
		exit_fractol(f, EXIT_SUCCESS);
	else if (key.key == MLX_KEY_UP)
		f->zoom_y -= .2 * f->zoom;
	else if (key.key == MLX_KEY_DOWN)
		f->zoom_y += .2 * f->zoom;
	else if (key.key == MLX_KEY_LEFT)
		f->zoom_x -= .2 * f->zoom;
	else if (key.key == MLX_KEY_RIGHT)
		f->zoom_x += .2 * f->zoom;
	ft_memset(f->valid_pixel, false, sizeof f->valid_pixel);
}

void	resize_hook(int w, int h, void *_f)
{
	t_fractol	*f;

	f = _f;
	assert_mlx(f, mlx_resize_image(f->img, w, h));
	assert_mlx(f, mlx_resize_image(f->iters_mem, w, h));
	f->iters = (uint32_t *)f->iters_mem->pixels;
	ft_memset(f->valid_pixel, false, sizeof f->valid_pixel);
}

void	scroll_hook(double xdelta, double ydelta, void *_f)
{
	t_fractol	*f;
	int32_t		mouse_x;
	int32_t		mouse_y;

	(void)xdelta;
	f = _f;
	mlx_get_mouse_pos(f->mlx, &mouse_x, &mouse_y);
	f->max_iterations += 5 * ydelta;
	if (f->max_iterations > MAX_ITERATIONS)
		f->max_iterations = MAX_ITERATIONS;
	else if (f->max_iterations < 8)
		f->max_iterations = 8;
	if (ydelta >= 0.)
	{
		f->zoom /= 1.5;
		f->zoom_x += f->zoom * ((double)(2 * mouse_x) / f->img->width - 1.);
		f->zoom_y += f->zoom * ((double)(2 * mouse_y) / f->img->height - 1.);
	}
	else
	{
		f->zoom *= 1.5;
		f->zoom_x -= f->zoom * ((double)(2 * mouse_x) / f->img->width - 1.);
		f->zoom_y -= f->zoom * ((double)(2 * mouse_y) / f->img->height - 1.);
	}
	ft_memset(f->valid_pixel, false, sizeof f->valid_pixel);
}

void	cursor_hook(double mouse_x, double mouse_y, void *_f)
{
	t_fractol	*f;
	double		aspect;

	f = _f;
	aspect = (double)f->img->width / f->img->height;
	f->julia_c = (t_complex){
		.re = aspect * (4. * mouse_x / f->img->width - 2.),
		.im = 4. * mouse_y / f->img->height - 2.
	};
	f->julia_c.re = f->julia_c.re * f->zoom + f->zoom_x;
	f->julia_c.im = f->julia_c.im * f->zoom + f->zoom_y;
	ft_memset(f->valid_pixel, false, sizeof f->valid_pixel);
}
