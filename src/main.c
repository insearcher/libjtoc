/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:45:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 16:48:18 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

// static void check(t_jnode *p)
// {
// 	if (!p)
// 		return ;
// 	if (p->type == number)
// 		printf("int: %d\n", *((int *)p->data));
// 	if (p->type == string)
// 		printf("str: %s\n", (char *)p->data);
// 	if (p->type == array)
// 	{
// 		printf("arr: \n");
// 		check(p->down);
// 	}
// 	if (p->type == object)
// 	{
// 		printf("obj: \n");
// 		check(p->down);
// 	}
// 	check(p->right);
// }

int	main(int argc, char **argv)
{
	t_jnode *res = NULL;
	if (argc == 2)
		res = jtoc_read(argv[1]);
	// check(res->down);
	t_jnode *test = jtoc_node_get_by_path(res, "friends.1.name");
	printf("%s\n", (char *)(test->data));
	return (0);
}
