/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:37:13 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 19:54:17 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_tag.h"
#include "ft_flags.h"
#include <libft.h>
#include <stdarg.h>
#include <stdlib.h>

#include <stdio.h>

static int	ft_print_substr(const char *str, size_t len)
{
	size_t	count;

	count = len;
	while (count--)
		ft_putchar_fd(*str++, 1);
	return (len);
}

static void	ft_print_subconv(t_fttag *tag, const char *conv, const char *pad)
{
	if (tag->flags && ft_strchr(tag->flags, '-'))
	{
		if (tag->type == 'c')
			ft_putchar_fd(*conv, 1);
		else
			ft_putstr_fd((char *)conv, 1);
		ft_putstr_fd((char *)pad, 1);
	}
	else
	{
		ft_putstr_fd((char *)pad, 1);
		if (tag->type == 'c')
			ft_putchar_fd(*conv, 1);
		else
			ft_putstr_fd((char *)conv, 1);
	}
}

static int	ft_print_conv(t_fttag *tag, const char *conv)
{
	const char		*pad;
	const char		*prefix;
	unsigned int	len;

	prefix = ft_handle_prefix(tag, conv);
	if (tag->type == 'c')
		len = 1;
	else
		len = ft_strlen(prefix);
	pad = ft_get_pad(tag, conv);
	if (!pad)
		return (-1);
	ft_print_subconv(tag, prefix, pad);
	len += ft_strlen(pad);
	free((char *)prefix);
	free((char *)pad);
	return (len);
}

static int	ft_rprintf(const char *format, va_list argv, int bcount)
{
	const char	*ptag;
	t_fttag		*tag;
	const char	*conv;

	ptag = ft_strchr(format, '%');
	if (!ptag)
	{
		ft_putstr_fd((char *)format, 1);
		return (bcount + ft_strlen(format));
	}
	else if (*(ptag + 1) == 0)
		return (bcount);
	bcount += ft_print_substr(format, ptag - format);
	tag = ft_get_tag(ptag, argv);
	if (!tag)
		return (ft_rprintf(ptag + 1, argv, bcount));
	conv = ft_conv_tag(tag, argv);
	format = ptag + tag->len;
	bcount += ft_print_conv(tag, conv);
	ft_free_tag(&tag);
	free((char *)conv);
	return (ft_rprintf(format, argv, bcount));
}

int	ft_printf(const char *format, ...)
{
	va_list		argv;
	int			bcount;

	if (!format)
		return (0);
	va_start(argv, format);
	bcount = ft_rprintf(format, argv, 0);
	va_end(argv);
	return (bcount);
}
