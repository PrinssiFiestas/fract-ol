/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:27:31 by lfiestas          #+#    #+#             */
/*   Updated: 2024/11/02 18:00:00 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

typedef unsigned int	t_uint;

typedef struct s_string
{
	char	*data;
	size_t	length;
	size_t	capacity;
}			t_string;

int			ft_printf(const char *fmt, ...);

t_string	str_new(size_t capacity);
void		str_reserve(t_string *str, size_t capacity);
t_string	*str_concat(t_string *str, const char *cstr);
t_string	*str_push(t_string *str, char c);
void		str_vprintf(t_string *str, const char *fmt, va_list ap);

#endif // FT_PRINTF_H
