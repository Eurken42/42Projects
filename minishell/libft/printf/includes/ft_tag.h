/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tag.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:52:41 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 20:16:41 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAG_H
# define FT_TAG_H
# include <stddef.h>
# include <stdarg.h>
# include <limits.h>
# define T_PREC_DFLT UINT_MAX

typedef struct s_fttag
{
	size_t			len;
	const char		*flags;
	unsigned int	width;
	unsigned int	precision;
	char			type;
}	t_fttag;

t_fttag		*ft_create_tag(void);
void		ft_free_tag(t_fttag **tag);
t_fttag		*ft_get_tag(const char *format, va_list argv);

const char	*ft_conv_tag(t_fttag *tag, va_list argv);

size_t		ft_parse_flags(const char *format, t_fttag *tag);
size_t		ft_parse_width(const char *format, t_fttag *tag, va_list argv);
size_t		ft_parse_prec(const char *format, t_fttag *tag, va_list argv);

#endif
