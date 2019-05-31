/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:24:02 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 02:01:31 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

static int	jtoc_find_comma(const char *str, int i)
{
	int	bro;
	int	bra;
	int	q;

	bro = 0;
	bra = 0;
	q = 0;
	while (str[i])
	{
		bro += (str[i] == '{' ? 1 : 0);
		bro -= (str[i] == '}' ? 1 : 0);
		bra += (str[i] == '[' ? 1 : 0);
		bra -= (str[i] == ']' ? 1 : 0);
		if (str[i] == '"')
			q = (q + 1) % 2;
		if (str[i] == ',' && !bro && !bra && !q)
			return (i);
		++i;
	}
	return (-1);
}

static int	jtoc_validate_number(const char *str, int b, int e)
{
	if (str[b] == '-')
		++b;
	while (b <= e && str[b] >= '0' && str[b] <= '9')
		++b;
	if ((b < e && str[b] != '.') || (b == e && str[b] == '.'))
		return (FUNCTION_FAILURE);
	if (str[b] == '.')
		++b;
	while (b <= e && str[b] >= '0' && str[b] <= '9')
		++b;
	return (b < e ?
		FUNCTION_FAILURE :
		FUNCTION_SUCCESS);
}

static int	jtoc_validate_string(const char *str, int b, int e)
{
	return (str[b] == '"' && str[e] == '"' ?
		FUNCTION_SUCCESS :
		FUNCTION_FAILURE);
}

static int	jtoc_validate_object(const char *str, int b, int e)
{
	int	c;

	if (str[e] == '\n')
		--e;
	if (str[b++] != '{' || str[e--] != '}')
		return (FUNCTION_FAILURE);
	while (b < e)
	{
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (jtoc_validate_token(str, b, c) < 0)
			return (FUNCTION_FAILURE);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

static int	jtoc_validate_array(const char *str, int b, int e)
{
	int	c;

	if (str[b++] != '[' || str[e--] != ']')
		return (FUNCTION_FAILURE);
	while (b < e)
	{
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (jtoc_validate_field(str, b, c))
			return (FUNCTION_FAILURE);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

int		jtoc_validate_field(const char *str, int c, int e)
{
	return ((str[c] == '"' && jtoc_validate_string(str, c, e) < 0) ||
		((str[c] == '-' || (str[c] >= '0' && str[c] <= '9')) &&
			jtoc_validate_number(str, c, e) < 0) ||
		(str[c] == '[' && jtoc_validate_array(str, c, e) < 0) ||
		(str[c] == '{' && jtoc_validate_object(str, c, e) < 0) ||
		(str[c] != '"' && str[c] != '[' && str[c] != '{' &&
			str[c] != '-' && (str[c] < '0' || str[c] > '9')));
}

// Валидируем поле типа "name": value,
int			jtoc_validate_token(const char *str, int b, int e)
{
	int	c;

	if ((c = jtoc_find(str, ':', b, F_RIGHT)) < 0 ||
		str[b] != '"' || str[c - 1] != '"' ||
		jtoc_validate_field(str, c + 1, e))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

// Валидируем всю строку
int			jtoc_validate(const char *str)
{
	return (jtoc_validate_object(str, 0, ft_strlen(str) - 1));
}
