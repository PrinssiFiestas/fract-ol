/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:33:36 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/04 12:07:08 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	exit_with_usage_info(const char *argv0)
{
	ft_printf("%s: usage options:\n\n", argv0);
	ft_printf("  %s mandelbrot\n", argv0);
	ft_printf("  %s julia\n", argv0);
	ft_printf("  %s julia <preset-1-to-5>\n", argv0);
	ft_printf("  %s julia <c-real> <c-imaginary>\n", argv0);
	ft_printf("  %s prinssi\n", argv0);
	exit(0);
}

static t_loop_hook	parse_argv(t_fractol *f, int argc, char **argv)
{
	const t_complex		julia_presets[] = {
	{-.4, .6}, {.285, .01}, {-.8, .1561}, {-.7269, .1889}, {.35, .35}};

	if (argc == 2 && ft_strncmp(argv[1], "mandelbrot", 32) == 0)
		return (draw_mandelbrot);
	else if (argc == 2 && ft_strncmp(argv[1], "prinssi", 32) == 0)
		return (draw_prinssi);
	else if (argc == 2 && ft_strncmp(argv[1], "julia", 32) == 0)
		return (draw_julia);
	else if (argc == 3 && ft_strncmp(argv[1], "julia", 32) == 0
		&& '1' <= argv[2][0] && argv[2][0] <= '5' && argv[2][1] == '\0')
	{
		f->julia_c = julia_presets[argv[2][0] - 1 - '0'];
		return (draw_julia);
	}
	else if (argc == 4 && ft_strncmp(argv[1], "julia", 32) == 0)
	{
		f->julia_c = (t_complex){str_to_f(argv[2]), str_to_f(argv[3])};
		return (draw_julia);
	}
	else
		exit_with_usage_info(argv[0]);
	return (NULL);
}

static uint8_t	u8_cos_1(double x)
{
	return (0xFF / 2 - 0xFF / 2 * cos(2. * M_PI * x / PALETTE_LENGTH));
}

static void	init_fractol(t_fractol *f, void (*drawer)(void *arg))
{
	size_t	i;

	f->zoom = 1.;
	f->max_iterations = 128;
	f->mlx = mlx_init(INIT_WIDTH, INIT_HEIGHT, "fractol", true);
	assert_mlx(f, f->mlx != NULL);
	f->img = mlx_new_image(f->mlx, INIT_WIDTH, INIT_HEIGHT);
	assert_mlx(f, f->img != NULL);
	assert_mlx(f, mlx_image_to_window(f->mlx, f->img, 0, 0) != -1);
	f->iters_mem = mlx_new_image(f->mlx, INIT_WIDTH, INIT_HEIGHT);
	f->iters = (uint32_t *)f->iters_mem->pixels;
	assert_mlx(f, f->iters_mem != NULL);
	mlx_key_hook(f->mlx, key_hook, f);
	mlx_resize_hook(f->mlx, resize_hook, f);
	mlx_scroll_hook(f->mlx, scroll_hook, f);
	assert_mlx(f, mlx_loop_hook(f->mlx, drawer, f));
	i = 0;
	while (i < PALETTE_LENGTH)
	{
		f->palette[i] = 0xFF000000u;
		f->palette[i] |= u8_cos_1(1 * i) << 0;
		f->palette[i] |= u8_cos_1(2 * i) << 8;
		f->palette[i] |= u8_cos_1(3 * i) << 16;
		++i;
	}
}

int	main(int argc, char **argv)
{
	static t_fractol	f;
	t_loop_hook			loop_hook;

	loop_hook = parse_argv(&f, argc, argv);
	init_fractol(&f, loop_hook);
	if (argc == 2 && ft_strncmp(argv[1], "julia", 32) == 0)
		mlx_cursor_hook(f.mlx, cursor_hook, &f);
	mlx_loop(f.mlx);
}
