/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:46:35 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/31 18:13:48 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

static int	get_next_hash(char **str)
{
	char	*dup;
	int		res;

	dup = *str;
	while (*dup != '.')
		++dup;
	if (*dup)
		*dup = '\0';
	res = ft_strhash(*str);
	*str = ++dup;
	return (res);
}

t_jnode	*jtoc_node_create(const char type, char *name, void *data)
{
	t_jnode	*res;
	char	*name_dup;

	if (!(res = (t_jnode *)malloc(sizeof(t_jnode))))
		return (NULL);
	res->type = type;
	res->hash = ft_strhash(name);
	res->data = data;
	res->right = NULL;
	res->down = NULL;
	return (res);
}

// int		jtoc_node_insert_by_path(t_jnode **parent, t_jnode *child,
// const char *path)
// {

// }

// int		jtoc_node_get_by_path(t_jnode **parent, const char *path)
// {

// }

void	jtoc_node_clear(t_jnode *cur)
{
	if (cur->right)
		jtoc_node_clear(cur->right);
	if (cur->down)
		jtoc_node_clear(cur->down);
	free(cur->data);
	free(cur);
}
