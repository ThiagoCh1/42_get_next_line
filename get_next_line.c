/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:58:38 by thribeir          #+#    #+#             */
/*   Updated: 2025/09/11 17:55:19 by thribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stash(fd, stash)
{
	size_t	nread;
	char	buf[BUFFER_SIZE + 1];

	while (gnl_strchr(slash, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
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
