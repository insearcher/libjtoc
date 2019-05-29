/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:45:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/29 19:33:25 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char *res = NULL;
	if (argc == 2)
		jtoc_read_file(argv[1], &res);
	jtoc_remove_spaces(&res);
	printf("%d\n", jtoc_validate(res));
	return (0);
}
