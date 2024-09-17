/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:53:46 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/29 14:19:09 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int			ft_printf(const char *format, ...);

void		ft_putchar_count(char c, int *count);
void		ft_putstr_count(char *str, int *count);
void		ft_itoa(int n, int *count);
void		ft_itoa_unsigned(unsigned int n, int *count);
void		ft_putchar_count(char c, int *count);
void		ft_putstr_count(char *str, int *count);
void		ft_putnbr_hexa_count(unsigned int nb, int *count, int up);
void		ft_putnbr_hexa_ptr_count(unsigned long int nb, int *count);

#endif
