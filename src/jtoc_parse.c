/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:22:42 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 17:05:43 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

static enum e_type	jtoc_get_field_type(const char f)
{
	if (f == '[')
		return (array);
	if (f == '{')
		return (object);
	if (f == '"')
		return (string);
	if (f == '-' || (f >= '0' && f <= '9'))
		return (number);
	return (none);
}

int					jtoc_parse_number(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;
	int		*data;

	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	if (!(data = (int *)malloc(sizeof(int))))
	{
		free(sub);
		return (FUNCTION_FAILURE);
	}
	*data = ft_atoi(sub);
	p->data = (void *)data;
	return (FUNCTION_SUCCESS);
}

int					jtoc_parse_string(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;

	++b;
	--e;
	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	p->data = (void *)sub;
	return (FUNCTION_SUCCESS);
}

int					jtoc_parse_array(t_jnode *p, const char *str, int b, int e)
{
	t_jnode	*child;
	char	*tmp;
	int		c;
	int		i;

	++b;
	--e;
	i = -1;
	while (b < e)
	{
		++i;
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (!(tmp = ft_itoa(i)))
			return (FUNCTION_FAILURE);
		child = jtoc_node_create(jtoc_get_field_type(str[b]), tmp, NULL);
		free(tmp);
		if (!child)
			return (FUNCTION_FAILURE);
		jtoc_node_add_child(p, child);
		jtoc_parse_value(child, str, b, c);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

int					jtoc_parse_value(t_jnode *p, const char *str, int b, int e)
{
	if ((p->type == array && jtoc_parse_array(p, str, b, e) < 0) ||
		(p->type == string && jtoc_parse_string(p, str, b, e) < 0) ||
		(p->type == object && jtoc_parse_object(p, str, b, e) < 0) ||
		(p->type == number && jtoc_parse_number(p, str, b, e) < 0))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

int					jtoc_parse_field(t_jnode *p, const char *str, int b, int e)
{
	t_jnode	*child;
	char	*name;
	int		c;

	c = jtoc_find(str, ':', b, F_RIGHT);
	if (!(name = ft_strsub(str, b + 1, c - b - 2)))
		return (FUNCTION_FAILURE);
	child = jtoc_node_create(jtoc_get_field_type(str[c + 1]), name, NULL);
	free(name);
	if (!child)
		return (FUNCTION_FAILURE);
	jtoc_node_add_child(p, child);
	jtoc_parse_value(child, str, c + 1, e);
	return (FUNCTION_SUCCESS);
}

int					jtoc_parse_object(t_jnode *p, const char *str, int b, int e)
{
	int	c;

	if (str[e] == '\n')
		--e;
	++b;
	--e;
	while (b < e)
	{
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (jtoc_parse_field(p, str, b, c) < 0)
			return (FUNCTION_FAILURE);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

t_jnode				*jtoc_parse(const char *str)
{
	t_jnode	*root;

	if (!(root = jtoc_node_create(none, "root", NULL)))
		return (NULL);
	if (jtoc_parse_object(root, str, 0, ft_strlen(str) - 1) < 0)
	{
		jtoc_node_clear(root);
		return (NULL);
	}
	return (root);
}
