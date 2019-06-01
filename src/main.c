/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:45:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 17:05:58 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

static void check(t_jnode *p, int i)
{
	int j = -1;
	if (!p)
		return ;
	while (++j < i)
		printf("  ");
	printf("%s", p->name);
	if (p->type == number)
		printf(" -> %d", *((int *)p->data));
	if (p->type == string)
		printf(" -> %s", (char *)p->data);
	printf("\n");
	check(p->down, i + 1);
	check(p->right, i);
}

int	main(int argc, char **argv)
{
	t_jnode *res = NULL;
	if (argc == 2)
		res = jtoc_read(argv[1]);
	check(res->down, 0);
	t_jnode *test = jtoc_node_get_by_path(res, "friends.1.name");
	printf("%s\n", (char *)(test->data));
	return (0);
}
