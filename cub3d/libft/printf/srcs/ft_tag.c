/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:31:35 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 20:17:40 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tag.h"
#include <libft.h>
#include <stdarg.h>
#include <stdlib.h>

t_fttag	*ft_create_tag(void)
{
	t_fttag	*tag;

	tag = ft_calloc(1, sizeof(t_fttag));
	if (!tag)
		return (NULL);
	tag->precision = T_PREC_DFLT;
	return (tag);
}

void	ft_free_tag(t_fttag **tag)
{
	if (!tag || !*tag)
		return ;
	free((char *)(*tag)->flags);
	free(*tag);
	*tag = NULL;
}

t_fttag	*ft_get_tag(const char *format, va_list argv)
{
	size_t			i;
	t_fttag			*tag;

	i = 1;
	tag = ft_create_tag();
	if (format[i] == '%')
	{
		tag->type = '%';
		tag->len = i + 1;
		return (tag);
	}
	i += ft_parse_flags(format + i, tag);
	i += ft_parse_width(format + i, tag, argv);
	i += ft_parse_prec(format + i, tag, argv);
	if (ft_strchr("cspdiuxX", format[i]))
	{
		tag->type = format[i];
		tag->len = i + 1;
	}
	else
		ft_free_tag(&tag);
	if (tag && ft_strchr("diuxX", tag->type) && tag->precision == T_PREC_DFLT)
		tag->precision = 1;
	return (tag);
}
