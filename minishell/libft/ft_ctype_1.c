/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:25:35 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/05 18:11:09 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (!ft_isalpha(c) || (c >= 'A' && c <= 'Z'))
		return (c);
	else
		return (c - 'a' + 'A');
}

int	ft_tolower(int c)
{
	if (!ft_isalpha(c) || (c >= 'a' && c <= 'z'))
		return (c);
	else
		return (c - 'A' + 'a');
}
