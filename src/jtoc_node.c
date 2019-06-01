/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:46:35 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 15:56:35 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

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

t_jnode		*jtoc_node_create(enum e_type type, char *name, void *data)
{
	t_jnode	*res;

	if (!(res = (t_jnode *)malloc(sizeof(t_jnode))))
		return (NULL);
	res->type = type;
	res->hash = ft_strhash(name);
	res->data = data;
	res->right = NULL;
	res->down = NULL;
	return (res);
}

int		jtoc_node_insert_by_path(t_jnode *root, t_jnode *child,
const char *path)
{
	t_jnode	*cur;

	if (!root)
		return (FUNCTION_FAILURE);
	cur = jtoc_node_get_by_path(root, path);
	if (cur->down)
	{
		cur = cur->down;
		while (cur->right)
			cur = cur->right;
		cur->right = child;
	}
	else
		cur->down = child;
	return (FUNCTION_SUCCESS);
}

void		jtoc_node_add_child(t_jnode *parent, t_jnode *child)
{
	t_jnode	*cur;

	if (!(parent->down))
	{
		parent->down = child;
		return ;
	}
	cur = parent->down;
	while (cur->right)
		cur = cur->right;
	cur->right = child;
}

t_jnode		*jtoc_node_get_by_path(t_jnode *parent, const char *path)
{
	t_jnode	*cur;
	char	*dupf;
	char	*dup;
	int		hash;

	if (!path || !parent || !(dup = ft_strdup(path)))
		return (NULL);
	dupf = dup;
	cur = parent;
	while ((hash = get_next_hash(&dup)) != 0)
	{
		cur = cur->down;
		while (cur && cur->hash != hash)
			cur = cur->right;
		if (!cur)
		{
			cur = NULL;
			break;
		}
	}
	free(dupf);
	return (cur);
}

void		jtoc_node_clear(t_jnode *cur)
{
	if (cur->right)
		jtoc_node_clear(cur->right);
	if (cur->down)
		jtoc_node_clear(cur->down);
	free(cur->data);
	free(cur);
}
