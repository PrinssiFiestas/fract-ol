/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:30:59 by lfiestas          #+#    #+#             */
/*   Updated: 2024/12/03 18:14:03 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_add(t_complex a, t_complex b)
{
	return ((t_complex){.re = a.re + b.re, .im = a.im + b.im});
}

t_complex	c_sub(t_complex a, t_complex b)
{
	return ((t_complex){.re = a.re - b.re, .im = a.im - b.im});
}

t_complex	c_mul(t_complex a, t_complex b)
{
	return ((t_complex){
		.re = a.re * b.re + a.im * b.im,
		.im = a.re * b.im + a.im * b.re
	});
}

t_complex	c_div(t_complex a, t_complex b)
{
	double	abs_b;

	abs_b = b.re * b.re + b.im * b.im;
	return ((t_complex){
		.re = (a.re * b.re + a.im * b.im) / abs_b,
		.im = (a.im * b.re - a.re * b.im) / abs_b
	});
}

t_complex	c_sqr(t_complex z)
{
	return ((t_complex){
		.re = z.re * z.re - z.im * z.im, .im = 2. * z.re * z.im});
}
