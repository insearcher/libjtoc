/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:34:11 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/29 19:32:54 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

char	*jtoc_strnew(size_t size)
{
	char	*res;
	size_t	i;

	if (!(res = (char *)malloc(size + 1)))
		return (NULL);
	i = -1;
	while (++i < size + 1)
		res[i] = '\0';
	return (res);
}

int		jtoc_is_space(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int		jtoc_skip_spaces(const char *str, int i)
{
	while (jtoc_is_space(str[i]))
		++i;
	return (i);
}

int		jtoc_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int		jtoc_find(const char *str, const char s, int i, int p)
{
	while (i >= 0 && str[i])
	{
		if (str[i] == s)
			return (i);
		if (p & F_ONLY_SPACES && !jtoc_is_space(str[i]))
			return (-1);
		i += p & F_RIGHT ? 1 : -1;
	}
	return (-1);
}

int		jtoc_max(int a, int b)
{
	return (a > b ? a : b);
}

static int	jtoc_strlen_without_spaces(char *str)
{
	int		ns;
	int		len;
	int		q;

	len = -1;
	ns = 0;
	q = 0;
	while (str[++len])
	{
		if (str[len] == '"')
			q = (q + 1) % 2;
		if (!jtoc_is_space(str[len]) || q)
			++ns;
	}
	return (ns);
}

int			jtoc_remove_spaces(char **str)
{
	int		ns;
	int		len;
	int		q;
	char	*tmp;

	if (!str || !*str || !(tmp = jtoc_strnew(jtoc_strlen_without_spaces(*str))))
		return (FUNCTION_FAILURE);
	len = -1;
	ns = -1;
	q = 0;
	while (str[0][++len])
	{
		if (str[0][len] == '"')
			q = (q + 1) % 2;
		if (!jtoc_is_space(str[0][len]) || q)
			tmp[++ns] = str[0][len];
	}
	free(*str);
	*str = tmp;
	return (FUNCTION_SUCCESS);
}
