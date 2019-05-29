/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_read_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:28:09 by sbednar           #+#    #+#             */
/*   Updated: 2019/05/29 00:51:02 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int	jtoc_read_file(const char *path, char **res)
{
	int		fd;
	int		len;
	char	buf[BUF_SIZE + 1];

	if (!res)
		return (FUNCTION_FAILURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FUNCTION_FAILURE);
	if ((len = read(fd, &buf, BUF_SIZE)) <= 0 || !(*res = jtoc_strnew(len)))
	{
		close(fd);
		return (FUNCTION_FAILURE);
	}
	while (--len >= 0)
		res[0][len] = buf[len];
	close(fd);
	return (FUNCTION_SUCCESS);
}
