/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:30:09 by scorreia          #+#    #+#             */
/*   Updated: 2021/10/15 14:30:09 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

/*#include <stdio.h>
int main(void)
{
    int i;

    i = -6;
    while (i++ <= 11)
    {
        if (ft_isalnum(i) == 1)
            printf("%d is digit !\n", i);
        else
            printf("%d is not digit !\n", i);
    }
    return (0);
}*/