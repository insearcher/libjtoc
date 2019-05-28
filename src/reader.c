/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:28:09 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/28 19:44:35 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int	jtoc_read_file(const char *path, char *res)
{
	int		fd;
	size_t	len;
	char	buf[BUF_SIZE + 1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FUNCTION_FAILURE);
	if ((len = read(fd, &buf, BUF_SIZE)) <= 0 || !(res = ft_strnew(len)))
	{
		close(fd);
		return (FUNCTION_FAILURE);
	}
	while (--len >= 0)
		res[len] = buf[len];
	close(fd);
	return (FUNCTION_SUCCESS);
}
