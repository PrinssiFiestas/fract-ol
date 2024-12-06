/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:34:34 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/04 07:28:12 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	str_to_f(const char *str)
{
	uint64_t	integer;
	uint64_t	fraction;
	size_t		fraction_power;
	double		sign;

	sign = 1.;
	if ((*str == '+' || *str == '-'))
		sign = 1. - 2 * (*str++ == '-');
	integer = 0;
	while ('0' <= *str && *str <= '9')
		integer = integer * 10 + *str++ - '0';
	if (*str == '.')
		++str;
	fraction = 0;
	fraction_power = 1;
	while ('0' <= *str && *str <= '9')
	{
		fraction_power *= 10;
		fraction = fraction * 10 + *str++ - '0';
	}
	return (sign * (integer + (double)fraction / fraction_power));
}

void	exit_fractol(t_fractol *f, int status)
{
	if (f->mlx != NULL)
	{
		mlx_delete_image(f->mlx, f->img);
		mlx_delete_image(f->mlx, f->iters_mem);
		free(f->mlx);
	}
	exit(status);
}

bool	assert_mlx(t_fractol *f, bool condition)
{
	if (condition == true)
		return (true);
	ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
	exit_fractol(f, EXIT_FAILURE);
	return (false);
}
