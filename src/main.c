/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:45:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 01:30:50 by sbednar          ###   ########.fr       */
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
	int ll = 4;
	t_jnode *p = jtoc_node_create(0, "", NULL);
	t_jnode *a = jtoc_node_create(0, "a", NULL);
	t_jnode *b1 = jtoc_node_create(0, "b1", NULL);
	t_jnode *b2 = jtoc_node_create(0, "b2", NULL);
	t_jnode *b3 = jtoc_node_create(0, "b3", NULL);
	t_jnode *c1 = jtoc_node_create(0, "c1", NULL);
	t_jnode *c2 = jtoc_node_create(0, "c2", NULL);
	t_jnode *d1 = jtoc_node_create(0, "d1", NULL);
	t_jnode *d2 = jtoc_node_create(0, "d2", &ll);
	jtoc_node_insert_by_path(p, a, "");
	jtoc_node_insert_by_path(p, b1, "a");
	jtoc_node_insert_by_path(p, b2, "a");
	jtoc_node_insert_by_path(p, b3, "a");
	jtoc_node_insert_by_path(p, c1, "a.b2");
	jtoc_node_insert_by_path(p, c2, "a.b2");
	jtoc_node_insert_by_path(p, d1, "a.b3");
	jtoc_node_insert_by_path(p, d2, "a.b3");
	t_jnode *ress = jtoc_node_get_by_path(p, "a.b3.d2");
	printf("found : %d\n", *((int *)(ress->data)));
	printf("%d\n", jtoc_validate(res));
	return (0);
}
