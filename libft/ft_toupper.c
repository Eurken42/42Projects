/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:45:43 by scorreia          #+#    #+#             */
/*   Updated: 2021/10/18 13:45:43 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    DESCRIPTION
       toupper() convertit la lettre c en majuscule si c'est pos­
       sible.

    VALEUR RENVOYÉE
       La valeur renvoyée est celle de la  lettre  convertie,  ou
       bien c si la conversion n'etait pas possible.

*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
