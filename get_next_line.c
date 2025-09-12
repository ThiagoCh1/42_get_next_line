/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:58:38 by thribeir          #+#    #+#             */
/*   Updated: 2025/09/12 18:11:15 by thribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stash(fd, stash)
{
	size_t	nread;
	char	buf[BUFFER_SIZE + 1];

	while (!gnl_strchr(stash, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == 0)
			return (stash);
		if (nread == -1)
			return (NULL);
		buf[nread] = '\0';
		stash = gnl_strjoin(stash, buf);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	stash = read_to_stash(fd, stash);
}
