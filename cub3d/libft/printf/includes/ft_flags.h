/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:00:31 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 20:14:25 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAGS_H
# define FT_FLAGS_H
# include "ft_tag.h"

unsigned int	ft_pad0len(t_fttag *tag);
const char		*ft_get_pad(t_fttag *tag, const char *conv);
const char		*ft_handle_prefix(t_fttag *tag, const char *conv);

#endif
