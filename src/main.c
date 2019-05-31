/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:45:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/31 18:15:51 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

static int	get_next_hash(char **str)
{
	char	*dup;
	int		res;

	dup = *str;
	while (*dup && *dup != '.')
		++dup;
	if (*dup)
		*dup = '\0';
	res = ft_strhash(*str);
	*str = ++dup;
	return (res);
}

int	main(int argc, char **argv)
{
	char *res = NULL;
	if (argc == 2)
		jtoc_read_file(argv[1], &res);
	jtoc_remove_spaces(&res);
	char *a = "abc.abc.abd";
	printf("%d\n", get_next_hash(&a));
	printf("%d\n", get_next_hash(&a));
	printf("%d\n", get_next_hash(&a));
	printf("%d\n", jtoc_validate(res));
	return (0);
}
