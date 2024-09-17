/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:05 by scorreia          #+#    #+#             */
/*   Updated: 2021/11/08 13:08:18 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*#include <stdio.h>
int main(void)
{
    int i;

    i = -6;
    while (i++ <= 11)
    {
        if (ft_isdigit(i) == 1)
            printf("%d is digit !\n", i);
        else
            printf("%d is not digit !\n", i);
    }
    return (0);
}*/
