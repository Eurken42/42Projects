/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:29:48 by gluisier          #+#    #+#             */
/*   Updated: 2021/11/22 19:08:02 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

char	*ft_itoaw(int nbr, unsigned int min_len, unsigned int min_digit);
char	*ft_uitoa(unsigned int u, unsigned int min_len);
char	*ft_ultohex(unsigned long long ul, int up, unsigned int min_len);

#endif
