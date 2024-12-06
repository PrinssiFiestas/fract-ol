/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:28:13 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/05 09:45:14 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <.MLX42.h>
# include <libft.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>

# define INIT_WIDTH 512
# define INIT_HEIGHT 512
# define MAX_ITERATIONS 512
# define PALETTE_LENGTH 1024

typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*iters_mem;
	uint32_t	*iters;
	double		zoom;
	double		zoom_x;
	double		zoom_y;
	t_complex	julia_c;
	bool		valid_pixel[4];
	size_t		valid_pixel_i;
	size_t		max_iterations;
	uint32_t	iters_per_pixel[MAX_ITERATIONS];
	uint32_t	palette[PALETTE_LENGTH];
}				t_fractol;

typedef void		(*t_loop_hook)(void *arg);
typedef uint32_t	(*t_fractal)(t_fractol *f, size_t ix, size_t iy, double ar);

uint32_t	mandelbrot(t_fractol *f, size_t ix, size_t iy, double aspect_ratio);
uint32_t	julia(t_fractol *f, size_t ix, size_t iy, double aspect_ratio);
uint32_t	prinssi(t_fractol *f, size_t ix, size_t iy, double aspect_ratio);

void		draw_mandelbrot(void *fractol);
void		draw_julia(void *fractol);
void		draw_prinssi(void *fractol);

t_complex	c_add(t_complex a, t_complex b);
t_complex	c_sub(t_complex a, t_complex b);
t_complex	c_mul(t_complex a, t_complex b);
t_complex	c_div(t_complex a, t_complex b);
t_complex	c_sqr(t_complex z);

double		str_to_f(const char *str);
bool		assert_mlx(t_fractol *f, bool condition);
void		exit_fractol(t_fractol *f, int status);

void		key_hook(mlx_key_data_t key, void *fractol);
void		resize_hook(int w, int h, void *fractol);
void		scroll_hook(double xdelta, double ydelta, void *fractol);
void		cursor_hook(double xpos, double ypos, void *fractol);

#endif
