/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:34:11 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 02:01:05 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int		jtoc_find(const char *str, const char s, int i, int p)
{
	while (i >= 0 && str[i])
	{
		if (str[i] == s)
			return (i);
		if (p & F_ONLY_SPACES && !ft_isstn(str[i]))
			return (-1);
		i += p & F_RIGHT ? 1 : -1;
	}
	return (-1);
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
		if (!ft_isstn(str[len]) || q)
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

	if (!str || !*str || !(tmp = ft_strnew(jtoc_strlen_without_spaces(*str))))
		return (FUNCTION_FAILURE);
	len = -1;
	ns = -1;
	q = 0;
	while (str[0][++len])
	{
		if (str[0][len] == '"')
			q = (q + 1) % 2;
		if (!ft_isstn(str[0][len]) || q)
			tmp[++ns] = str[0][len];
	}
	free(*str);
	*str = tmp;
	return (FUNCTION_SUCCESS);
}
