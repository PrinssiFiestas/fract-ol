/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:36:19 by lfiestas          #+#    #+#             */
/*   Updated: 2024/11/07 10:10:29 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

static char	*convert_i(char *buf, int64_t i)
{
	size_t	length;
	int64_t	n;

	if (i == 0)
	{
		buf[0] = '0';
		return (buf);
	}
	n = i;
	length = 0;
	if (n < 0)
	{
		buf[length++] = '-';
		n = -n;
	}
	while (n != 0 && 1 + length++)
		n /= 10;
	n = i * (1 - 2 * (i < 0));
	while (n != 0)
	{
		buf[--length] = n % 10 + '0';
		n /= 10;
	}
	return (buf);
}

static char	*convert_x(char *buf, uint64_t num, char hex_10)
{
	size_t		l;
	uint64_t	n;

	if (num == 0)
	{
		buf[0] = '0';
		return (buf);
	}
	l = 0;
	n = num;
	while (n != 0 && 1 + l++)
		n /= 0x10;
	n = num;
	while (n != 0)
	{
		if (n % 0x10 < 10)
			buf[--l] = n % 0x10 + '0';
		else
			buf[--l] = n % 0x10 + hex_10 - 10;
		n /= 0x10;
	}
	return (buf);
}

static char	*convert_p(char *buf, void *ptr)
{
	if (ptr == NULL)
		return ("(nil)");
	*buf++ = '0';
	*buf++ = 'x';
	return (convert_x(buf, (uintptr_t)ptr, 'a') - 2);
}

void	str_vprintf(t_string *str, const char *fmt, va_list ap)
{
	while (*fmt != '\0')
	{
		if (fmt[0] == '%' && fmt[1] == '%')
			str_push(str, '%');
		else if (fmt[0] == '%' && fmt[1] == 'c')
			str_push(str, (char)va_arg(ap, int));
		else if (fmt[0] == '%' && fmt[1] == 's')
			str_concat(str, va_arg(ap, char *));
		else if (fmt[0] == '%' && fmt[1] == 'p')
			str_concat(str, convert_p((char [24]){}, va_arg(ap, void *)));
		else if (fmt[0] == '%' && fmt[1] == 'd')
			str_concat(str, convert_i((char [24]){}, va_arg(ap, int)));
		else if (fmt[0] == '%' && fmt[1] == 'i')
			str_concat(str, convert_i((char [24]){}, va_arg(ap, int)));
		else if (fmt[0] == '%' && fmt[1] == 'u')
			str_concat(str, convert_i((char [24]){}, va_arg(ap, t_uint)));
		else if (fmt[0] == '%' && fmt[1] == 'x')
			str_concat(str, convert_x((char [24]){}, va_arg(ap, t_uint), 'a'));
		else if (fmt[0] == '%' && fmt[1] == 'X')
			str_concat(str, convert_x((char [24]){}, va_arg(ap, t_uint), 'A'));
		else
			str_push(str, *fmt--);
		fmt += 2;
	}
}

int	ft_printf(const char *fmt, ...)
{
	int			result;
	va_list		args;
	t_string	str;

	va_start(args, fmt);
	str = str_new(1024);
	str_vprintf(&str, fmt, args);
	write(STDOUT_FILENO, str.data, str.length);
	result = str.length;
	free(str.data);
	return (result);
	va_end(args);
	return (result);
}
