/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:26:44 by thribeir          #+#    #+#             */
/*   Updated: 2025/10/14 05:05:51 by thribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_to_stash_bonus(int fd, char *stash)
{
	ssize_t	nread;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!gnl_strchr(stash, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread <= 0)
		{
			free(buf);
			if (nread == -1 || !stash || !stash[0])
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

char	*get_line_bonus(char *stash)
{
	char		*line;
	size_t		i;
	size_t		j;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = malloc(i + 1);
	if (line == NULL)
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

char	*new_stash_bonus(char *stash)
{
	char	*new_stash;
	char	*new_pos;
	size_t	i;

	new_pos = gnl_strchr(stash, '\n');
	if (new_pos == NULL)
	{
		free(stash);
		return (NULL);
	}
	new_pos += 1;
	new_stash = malloc(gnl_strlen(new_pos) + 1);
	if (new_stash == NULL)
	{
		free(stash);
		return (NULL);
	}
	i = -1;
	while (++i < gnl_strlen(new_pos))
		new_stash[i] = new_pos[i];
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash_bonus(fd, stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	line = get_line_bonus(stash[fd]);
	stash[fd] = new_stash_bonus(stash[fd]);
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
