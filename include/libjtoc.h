/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libjtoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:28:19 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/29 16:38:44 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBJTOC_H
# define LIBJTOC_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define FUNCTION_SUCCESS	0
# define FUNCTION_FAILURE	-1

# define BUF_SIZE			(1 << 16)

# define TYPE_NUMBER		(1 << 0)
# define TYPE_STRING		(1 << 1)
# define TYPE_ARRAY			(1 << 2)
# define TYPE_TOKEN			(1 << 3)

# define F_RIGHT			(1 << 0)
# define F_ONLY_SPACES		(1 << 1)

typedef struct				s_jtoken
{
	char					type;
	char					*name;
	void					*data;
	struct s_jtoken			*next;
}							t_jtoken;

char						*jtoc_strnew(size_t size);
int							jtoc_strlen(const char *str);

int							jtoc_is_space(const char c);
int							jtoc_skip_spaces(const char *str, int i);

int							jtoc_find(const char *str, const char s, int i, int d);

int							jtoc_read_file(const char *path, char **res);
int							jtoc_validate(const char *str);
int							jtoc_validate_token(const char *str, int b, int e);

#endif
