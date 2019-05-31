/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:51:06 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 01:38:26 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strhash(const char *str)
{
	int	res;
	int	p;
	int	i;

	res = 0;
	p = 1;
	i = -1;
	while (str[++i])
	{
		res = (res + (str[i] - 'a' + 1) * p) % HASH_M;
		p = (p * HASH_P) % HASH_M;
	}
	return (res);
}
