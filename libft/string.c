/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:15 by lfiestas          #+#    #+#             */
/*   Updated: 2024/11/02 18:00:27 by lfiestas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

t_string	str_new(size_t capacity)
{
	t_string	str;

	str.data = malloc(capacity + sizeof"");
	str.length = 0;
	str.capacity = capacity;
	return (str);
}

void	str_reserve(t_string *str, size_t capacity)
{
	char	*temp;
	size_t	i;

	if (capacity >= str->capacity)
	{
		while (capacity >= str->capacity && str->capacity != 0)
			str->capacity *= 2;
		temp = malloc(str->capacity + sizeof"");
		i = 0;
		while (i < str->length)
		{
			temp[i] = str->data[i];
			++i;
		}
		free(str->data);
		str->data = temp;
	}
}

t_string	*str_concat(t_string *str, const char *cstr)
{
	size_t	cstr_length;
	size_t	i;

	if (cstr == NULL)
		return (str_concat(str, "(null)"));
	cstr_length = 0;
	while (cstr[cstr_length] != '\0')
		++cstr_length;
	str_reserve(str, str->length + cstr_length);
	i = 0;
	while (i < cstr_length)
	{
		str->data[str->length++] = cstr[i];
		++i;
	}
	str->data[str->length] = '\0';
	return (str);
}

t_string	*str_push(t_string *str, char c)
{
	str_reserve(str, str->length + 1);
	str->data[str->length++] = c;
	return (str);
}
