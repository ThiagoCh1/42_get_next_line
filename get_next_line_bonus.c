/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:26:44 by thribeir          #+#    #+#             */
/*   Updated: 2025/10/14 23:27:57 by thribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_to_stash(int fd, char *stash)
{
	ssize_t	nread;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!stash || !gnl_strchr(stash, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread <= 0)
		{
			free(buf);
			if (nread == -1 || !stash || stash[0] == '\0')
			{
				free(stash);
				return (NULL);
			}
			return (stash);
		}
		buf[nread] = '\0';
		stash = gnl_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

static char	*get_linee(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*new_stash(char *stash)
{
	char	*nl;
	char	*res;
	size_t	len;

	nl = gnl_strchr(stash, '\n');
	if (nl == NULL || *(nl + 1) == '\0')
	{
		free(stash);
		return (NULL);
	}
	nl++;
	len = gnl_strlen(nl);
	res = malloc(len + 1);
	if (!res)
	{
		free(stash);
		return (NULL);
	}
	ft_strlcpy(res, nl, len + 1);
	free(stash);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_linee(stash[fd]);
	stash[fd] = new_stash(stash[fd]);
	return (line);
}

/*#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc < 2)
	{
		printf("Usage: %s <file1> [file2 ...]\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			i++;
			continue ;
		}
		printf("\n=== Reading %s ===\n", argv[i]);
		while ((line = get_next_line_bonus(fd)) != NULL)
		{
			printf("%s", line); // line already has '\n' if present
			free(line);
		}
		close(fd);
		i++;
	}
	return (0);
}
*/
