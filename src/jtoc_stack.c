/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:41:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 14:48:20 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

t_stack						*stack_create(void *data)
{
	t_stack	*res;

	if (!(res = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	res->data = data;
	res->next = NULL;
	return (res);
}

void						stack_push(t_stack **root, t_stack *node)
{
	if (!root)
		return ;
	node->next = *root;
	*root = node;
}

t_stack						*stack_pop(t_stack **root)
{
	t_stack	*res;

	if (!root)
		return (NULL);
	res = *root;
	if (*root)
		*root = (*root)->next;
	return (res);
}

void						stack_clear(t_stack *root)
{
	if (root->next)
		stack_clear(root->next);
	free(root->data);
	free(root);
}
