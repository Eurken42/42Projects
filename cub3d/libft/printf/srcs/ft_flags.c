/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:04:01 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 19:53:30 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_flags.h"
#include "ft_tag.h"
#include <libft.h>
#include <stdlib.h>

unsigned int	ft_pad0len(t_fttag *tag)
{
	if (tag->flags && ft_strchr(tag->flags, '0') && !ft_strchr(tag->flags, '-')
		&& ft_strchr("diuxX", tag->type) && tag->precision == 1)
		return (tag->width);
	else
		return (0);
}

const char	*ft_get_pad(t_fttag *tag, const char *conv)
{
	char			*pad;
	char			fill;
	unsigned int	len;

	if (tag->type == 'c')
		len = 1;
	else
		len = ft_strlen(conv);
	fill = ' ';
	if (tag->flags && ft_strchr(tag->flags, '0')
		&& !ft_strchr("diuxX", tag->type))
		fill = '0';
	if (len < tag->width)
	{
		pad = ft_calloc(tag->width - len + 1, sizeof(char));
		if (pad)
			ft_memset(pad, fill, tag->width - len);
	}
	else
		pad = ft_strdup("");
	return (pad);
}

const char	*ft_handle_prefix(t_fttag *tag, const char *conv)
{
	char	*prefixed;
	char	prefix;

	if ((tag->type == 'd' || tag->type == 'i') && conv[0] != '-')
	{
		if (tag->flags && ft_strchr(tag->flags, '+'))
			prefix = '+';
		else if (tag->flags && ft_strchr(tag->flags, ' '))
			prefix = ' ';
		else
			return (ft_strdup(conv));
		if (conv[0] != '0' || ft_strlen(conv) == 1)
		{
			prefixed = ft_calloc(ft_strlen(conv) + 2, sizeof(char));
			prefixed[0] = prefix;
			ft_strlcat(prefixed, conv, ft_strlen(conv) + 2);
		}
		else
		{
			prefixed = ft_strdup(conv);
			prefixed[0] = prefix;
		}
		return (prefixed);
	}
	return (ft_strdup(conv));
}
