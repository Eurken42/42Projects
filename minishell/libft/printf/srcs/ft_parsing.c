/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:59:51 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 20:19:01 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tag.h"
#include <libft.h>
#include <stddef.h>

size_t	ft_parse_flags(const char *format, t_fttag *tag)
{
	size_t	i;

	i = 0;
	while (ft_strchr("-+ #0", format[i]))
		++i;
	tag->flags = ft_substr(format, 0, i);
	return (i);
}

static unsigned int	ft_parse_uint(const char *format, size_t *i)
{
	size_t	start;

	start = *i;
	while (ft_isdigit(format[*i]))
		++*i;
	return (ft_atoi(format + start));
}

size_t	ft_parse_width(const char *format, t_fttag *tag, va_list argv)
{
	size_t	i;

	i = 0;
	if (*format == '*')
	{
		tag->width = va_arg(argv, unsigned int);
		++i;
	}
	else
		tag->width = ft_parse_uint(format, &i);
	return (i);
}

size_t	ft_parse_prec(const char *format, t_fttag *tag, va_list argv)
{
	size_t	i;

	i = 0;
	if (*format == '.')
	{
		++i;
		if (format[i] == '*')
		{
			tag->precision = va_arg(argv, unsigned int);
			++i;
		}
		else
			tag->precision = ft_parse_uint(format, &i);
	}
	return (i);
}
