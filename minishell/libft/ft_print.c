/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:24:38 by gluisier          #+#    #+#             */
/*   Updated: 2022/05/17 11:19:33 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;
	int				i;
	char			str[11];

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)((n + 1) * -1) + 1;
	}
	else
		nbr = (unsigned int)n;
	*str = '0' + nbr % 10;
	nbr /= 10;
	i = 1;
	while (nbr)
	{
		str[i++] = '0' + nbr % 10;
		nbr /= 10;
	}
	while (i--)
		ft_putchar_fd(str[i], fd);
}
