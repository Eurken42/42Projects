/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:39:00 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 19:52:56 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags.h"
#include "ft_tag.h"
#include "ft_utils.h"
#include <libft.h>
#include <stdarg.h>
#include <stdlib.h>

static const char	*ft_conv_itag(t_fttag *tag, va_list argv)
{
	char			*conv;
	unsigned int	min_len;

	min_len = ft_pad0len(tag);
	if (tag->precision != T_PREC_DFLT && tag->precision > min_len)
		min_len = tag->precision;
	if (tag->type == 'u')
		conv = ft_uitoa(va_arg(argv, unsigned int), min_len);
	else
		conv = ft_itoaw(va_arg(argv, int), ft_pad0len(tag), tag->precision);
	return (conv);
}

static const char	*ft_conv_stag(t_fttag *tag, va_list argv)
{
	char			*conv;
	char			*s;
	unsigned int	prec;

	if (tag->type == 'c')
	{
		conv = ft_calloc(2, sizeof(char));
		if (conv)
			conv[0] = (char) va_arg(argv, int);
	}
	else
	{
		s = va_arg(argv, char *);
		if (!s)
			s = "(null)";
		prec = ft_strlen(s);
		if (tag->precision < ft_strlen(s))
			prec = tag->precision;
		conv = ft_substr(s, 0, prec);
	}
	return (conv);
}

static const char	*ft_conv_ptag(t_fttag *tag, va_list argv)
{
	char	*conv;
	char	*hex;

	(void) tag;
	hex = ft_ultohex(va_arg(argv, unsigned long long), 0, 0);
	conv = ft_strjoin("0x", hex);
	free(hex);
	return (conv);
}

static const char	*ft_conv_xtag(t_fttag *tag, va_list argv)
{
	char			*conv;
	char			*hex;
	unsigned int	min_len;

	min_len = ft_pad0len(tag);
	if (tag->precision != T_PREC_DFLT && tag->precision > min_len)
		min_len = tag->precision;
	if (tag->type == 'x')
		hex = ft_ultohex(va_arg(argv, unsigned int), 0, min_len);
	else
		hex = ft_ultohex(va_arg(argv, unsigned int), 1, min_len);
	if (tag->flags && ft_strchr(tag->flags, '#')
		&& (ft_strlen(hex) != 1 || hex[0] != '0'))
	{
		if (tag->type == 'x')
			conv = ft_strjoin("0x", hex);
		else
			conv = ft_strjoin("0X", hex);
		free(hex);
	}
	else
		conv = hex;
	return (conv);
}

const char	*ft_conv_tag(t_fttag *tag, va_list argv)
{
	if (!tag)
		return (ft_strdup(""));
	if (tag->type == '%')
		return (ft_strdup("%"));
	else if (tag->type == 'd' || tag->type == 'i' || tag->type == 'u')
		return (ft_conv_itag(tag, argv));
	else if (tag->type == 'c' || tag->type == 's')
		return (ft_conv_stag(tag, argv));
	else if (tag->type == 'p')
		return (ft_conv_ptag(tag, argv));
	else if (tag->type == 'x' || tag->type == 'X')
		return (ft_conv_xtag(tag, argv));
	return (ft_strdup(""));
}
